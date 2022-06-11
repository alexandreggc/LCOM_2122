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

int (kbd_get_size_bb)(){
  return size;
}
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

int is_two_byte(){
  return two_byte;
}
int kbd_error_occured(){
  return kbd_error;
}

void keyboard_get_key(uint8_t *key){
  memcpy(key, bb, size);
}

int (keyboard_check_esc)(uint8_t code[2]){
  if(two_byte == 0 && code[0] == ESC_B_CODE)
    return 1;
  return OK;
}

int (kbd_process_key)(uint8_t bbyte[2], keys_t *keys){
  if(size == 2){
      uint8_t lsb, msb;
      uint16_t arrowCodes[8] = {ARROWUP_M_CODE, ARROWUP_B_CODE, ARROWLEFT_M_CODE, ARROWLEFT_B_CODE, ARROWDOWN_M_CODE, ARROWDOWN_B_CODE, ARROWRIGHT_M_CODE, ARROWRIGHT_B_CODE};
      for(uint8_t i = 0; i < 8; i++){
        util_get_LSB(arrowCodes[i], &lsb);
        util_get_MSB(arrowCodes[i], &msb);
        if(bbyte[0] == msb && bbyte[1] == lsb){
          switch (i){
          case 0:{
            keys->up_pressed = 1;
            break;
          }
          case 1:{
            keys->up_pressed = 0;
            break;
          }
          case 2:{
            keys->left_pressed = 1;
            break;
          }
          case 3:{
            keys->left_pressed = 0;
            break;
          }
          case 4:{
            keys->down_pressed = 1;
            break;
          }
          case 5:{
            keys->down_pressed = 0;
            break;
          }
          case 6:{
            keys->right_pressed = 1;
            break;
          }
          case 7:{
            keys->right_pressed = 0;
            break;
          }
          default:
            break;
          }
        } 
      }
    }
  else{
    switch (bbyte[0]){
    case ESC_B_CODE: return 1;
    case W_M_CODE: {
      keys->up_pressed = 1;
      break;
    }
    case W_B_CODE: {
      keys->up_pressed = 0;
      break;
    }
    case A_M_CODE: {
      keys->left_pressed = 1;
      break;
    }
    case A_B_CODE: {
      keys->left_pressed = 0;
      break;
    }
    case S_M_CODE: {
      keys->down_pressed = 1;
      break;
    }
    case S_B_CODE: {
      keys->down_pressed = 0;
      break;
    }
    case D_M_CODE: {
      keys->right_pressed = 1;
      break;
    }
    case D_B_CODE: {
      keys->right_pressed = 0;
      break;
    }
    case SPACEBAR_M_CODE: {
      keys->space_pressed = 1;
      break;
    }
    case SPACEBAR_B_CODE: {
      keys->space_pressed = 0;
      break;
    }
    default:
      break;
    } 
  }
  return OK;
}
