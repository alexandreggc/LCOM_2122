#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "keyboard_macros.h"
#include "keyboard.h"

int kbd_hook_id = 1;
uint8_t bb[2];
bool two_byte = 0;
int size = 1;
int kbd_error = 0;
extern uint8_t kbc_cmd_byte;

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

void (keyboard_get_code)(bool *make, uint8_t bb[2]){
  if(size==1)
    *make = !((bb[0] >> 7) == 1);
  else
      *make = !((bb[1] >> 7) == 1);

}

int (keyboard_check_esc)(uint8_t bb[2]){
  if(two_byte == 0 && bb[0] == ESC_CODE)
    return 1;
  return OK;
}

int(kbd_enable_int)(){
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
