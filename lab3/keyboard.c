#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"
#include "keyboard_macros.h"
#include "keyboard.h"

int hook_id = 0;
uint8_t bb[2];
uint8_t two_byte = 0;
int size = 1;
int kbd_error = 0;

int (timer_subscribe_int)(uint8_t *bit_no) {
  *bit_no = hook_id;
  return sys_irqsetpolicy(KB_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id);
}

int (timer_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_id);
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
  uint8_t commandByte;
  util_sys_inb(STAT_REG, &commandByte);
  if ()
  sys_outb(STAT_REG, READ_KBC);
  util_sys_inb(OUT_BUF, &commandByte)
  commandByte |= ENABLE_INT;
  sys_outb(STAT_REG, WRITE_KBC);
  sys_outb(OUT_BUF, commandByte);
}
