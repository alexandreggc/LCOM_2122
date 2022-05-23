#include "mouse.h"

#include <stdint.h>

int mouse_hook_id = 1;
int mouse_ih_counter;


uint8_t bb[3];

int (mouse_subscribe_int)(uint8_t *bit_no) {
  *bit_no = mouse_hook_id;
  return sys_irqsetpolicy(IRQ_LINE, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id);
}

int (disable_irq)(){
  return sys_irqdisable(&mouse_hook_id);
}

int (enable_irq)(){
  return sys_irqenable(&mouse_hook_id);
}

int (mouse_unsubscribe_int)() {
  return sys_irqrmpolicy(&mouse_hook_id);
}

int (mouse_parse_packet)(struct packet *pp){
  for(int byte_n = 0; byte_n < 3; byte_n++){
    pp->bytes[byte_n] = bb[byte_n];
  }
  pp->rb       = pp->bytes[0] & RIGHT_BUTTON;
  pp->mb       = pp->bytes[0] & MIDDLE_BUTTON;
  pp->lb       = pp->bytes[0] & LEFT_BUTTON;
  pp->delta_x  = (int16_t)((bb[0] & X_SIGN) != 0) | pp->bytes[1];
  pp->delta_y  = (int16_t)((bb[0] & Y_SIGN) != 0) | pp->bytes[2];
  pp->x_ov     = pp->bytes[0] & X_OVFL;
  pp->y_ov     = pp->bytes[0] & Y_OVFL;
  return OK;
  }

void (mouse_ih)() {
  if(mouse_ih_counter >= 3){
    mouse_ih_counter = 0;
  }
  uint8_t byte;
  util_sys_inb(OUT_BUF, &byte);
  bb[mouse_ih_counter++] = byte;
}

