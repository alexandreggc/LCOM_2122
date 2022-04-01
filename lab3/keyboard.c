#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"
#include "keyboard_macros.h"

int hook_id = 0;
uint8_t bb[2];

int (keyboard_subscribe_int)(uint8_t *bit_no) {
  *bit_no = hook_id;
  return sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id);
}

int (keyboard_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_id);
}

void (kbc_ih)() {
  uint8_t value;
  util_sys_inb(OUT_BUF,&value);
  if(value == TWO_BYTE_CODE) {
    bb[0] = value;
  }
  else {
    bb[1] = value;
  }
}