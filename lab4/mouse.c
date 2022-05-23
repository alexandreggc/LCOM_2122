#include "mouse.h"
#include "keyboard.h"
#include "keyboard_macros.h"

#include <stdint.h>

int mouse_hook_id = 2;
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
  pp->delta_x  = (bb[0] & X_SIGN) ? 0xff00 | pp->bytes[1] : pp->bytes[1];
  pp->delta_y  = (bb[0] & Y_SIGN) ? 0xff00 | pp->bytes[2] : pp->bytes[2];
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
  if((byte & FIRST_BYTE_ID) || mouse_ih_counter){
    bb[mouse_ih_counter++] = byte;
  }
}

int (disable_data_reporting)(){
  uint8_t byte;
  sys_outb(CTRL_REG, MOUSE_WRITE_CMD);
  sys_outb(IN_BUF, DISABLE_DATA_REPORT);
  tickdelay(micros_to_ticks(ACKS_DELAY));
  if (util_sys_inb(OUT_BUF, &byte) && byte != ACK) return 1;
  return OK;
}

int (mouse_issue_cmd)(uint8_t cmd) {
    int ret;
    uint8_t ack = 0;
    for (unsigned int i = 0; i < KBC_NUM_TRIES; i++) {
        if ((ret = kbd_write_command(MOUSE_WRITE_CMD, cmd, true))) return ret;
        if ((ret = mouse_read_byte(&ack))) return ret;
        if (ack == ACK) return OK;
        else return 1;
        tickdelay(micros_to_ticks(DELAY_US));
    }
    return 1;
}

int (mouse_read_byte)(uint8_t *byte) {
    int ret = 0;
    uint8_t stat;
    for(int i = 0; i < KBC_NUM_TRIES; ++i){
        if((ret = util_sys_inb(STAT_REG, &stat))) return ret;
        if((stat & OBF_FULL) && (stat & AUX_MOUSE)) {
            if(stat & (KBC_PAR_ERR | KBC_TO_ERR)) return 1;
            if((ret = util_sys_inb(OUT_BUF, byte))) return ret;
            else return OK;
        }
        tickdelay(micros_to_ticks(DELAY_US));
    }
    return 1;
}
