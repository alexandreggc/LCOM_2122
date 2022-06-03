#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "keyboard.h"


int kbd_hook_id = 1;
uint8_t bb[2];
bool two_byte = 0;
int size = 1;
int kbd_error = 0;
//extern uint8_t kbc_cmd_byte;


int (kbd_subscribe_int)(uint8_t *bit_no) {
  *bit_no = kbd_hook_id;
  return sys_irqsetpolicy(KB_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &kbd_hook_id);
}

int (kbd_unsubscribe_int)() {
  return sys_irqrmpolicy(&kbd_hook_id);
}

void (kbc_ih)() {
  uint8_t value;
  size = 1;
  kbd_error = 0;

  util_sys_inb(STAT_REG, &value);

  value = value >> 6;
  if(value == STATUS_REG_ERR)
    kbd_error = 1;
  util_sys_inb(OUT_BUF,&value);
  process_scancode(value);
}

void (keyboard_get_code)(bool *make, uint8_t bbyte[2]){
  if(size==1)
    *make = !((bbyte[0] >> 7) == 1);
  else
      *make = !((bbyte[1] >> 7) == 1);
}

int (keyboard_process_key)(uint8_t bbyte[2], sprite_t* sp){
  int h_dir = REST, v_dir = REST;
    if(size == 2){
      uint8_t lsb, msb;
      uint16_t arrowCodes[4] = {ARROWUP_CODE, ARROWLEFT_CODE, ARROWDOWN_CODE, ARROWRIGHT_CODE};
      for(uint8_t i = 0; i < 4; i++){
        util_get_LSB(arrowCodes[i], &lsb);
        util_get_MSB(arrowCodes[i], &msb);
        if(bbyte[0] == msb && bbyte[1] == lsb){
          switch (i){
          case 0:{
            v_dir = UP;
            break;
          }
          case 1:{
            h_dir = LEFT;
            break;
          }
          case 2:{
            v_dir = DOWN;
            break;
          }
          case 3:{
            h_dir = RIGHT;
            break;
          }
          default:
            break;
          }
          break;
        } 
      }
    }
  else{
    switch (bbyte[0])
    {
    case ESC_CODE: return 1;
    case W_CODE: {
      v_dir = UP;
      break;
      }
    case A_CODE: {
      h_dir = LEFT;
      break;
      }
      case S_CODE: {
        v_dir = DOWN;
        break;
      }
      case D_CODE: {
        h_dir = RIGHT;
        break;
      }
      case SPACEBAR_CODE: {
        break;
      }
    default:
      break;
    } 
  }

  sprite_set_speed(sp, h_dir * PLAYER_SPEED, v_dir * PLAYER_SPEED);
  sprite_update_pos(sp);
  return OK;
}

int(kbd_enable_int)(){
  uint8_t kbc_cmd_byte=0;
  kbd_write_command(READ_CMD_BYTE, 0, false);
  kbd_read_outbuf(&kbc_cmd_byte);
  kbc_cmd_byte |= KBC_ENABLE_INT;
  kbd_write_command(WRITE_CMD_BYTE, kbc_cmd_byte, true);
  return OK;
}

int (kbd_write_command)(uint8_t kbc_cmd, uint8_t arg, bool has_arg){
  uint8_t stat;
  while(1) {
    util_sys_inb(STAT_REG, &stat); /* assuming it returns OK */
    /* loop while 8042 input buffer is not empty */
    if( (stat & IBF_FULL) == 0 ) {
      sys_outb(CMD_REG, kbc_cmd); /* no args command */
      if (has_arg){
        sys_outb(OUT_BUF, arg);
      }
      return OK;
    }
    tickdelay(micros_to_ticks(DELAY_US));
  }
  return OK;
}

int (kbd_read_outbuf)(uint8_t *data){
  uint8_t stat, d_read;
  while( 1 ) {
    util_sys_inb(STAT_REG, &stat);
    if( stat & OBF_FULL ) {
      util_sys_inb(OUT_BUF, &d_read); /* ass. it returns OK */
      if ((stat & (KBC_PAR_ERR | KBC_TO_ERR)) == 0){
        *data = d_read;
        return OK;
      }
      else return 1;
    }
    tickdelay(micros_to_ticks(DELAY_US));
  }
  return OK;
}

void (kbd_polling)(){
  uint8_t value;
  size = 1;
  kbd_error = kbd_read_outbuf(&value);
  process_scancode(value);
}

void (process_scancode)(uint8_t value){
  if(!kbd_error){
    if(two_byte) {
      bb[1] = value;
      two_byte = 0;
      size++;
    }
    else if(value == TWO_BYTE_CODE){
      bb[0] = value;
      two_byte = 1;
    }
    else
      bb[0] = value;
  }
}
