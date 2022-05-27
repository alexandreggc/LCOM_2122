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

/*
struct mouse_ev* mouse_detect_event(struct packet *pp) {
    static struct mouse_ev event;
    static uint8_t last = 0;

    if (pp == NULL) return &event;

    // current button presses
    uint8_t button_presses = pp->bytes[0] & (LEFT_BUTTON | RIGHT_BUTTON | MIDDLE_BUTTON);
    int16_t delta_x = pp->delta_x;
    int16_t delta_y = pp->delta_y;

    if ((button_presses ^ last) == LEFT_BUTTON && !(last & LEFT_BUTTON)) {
        event.type = LB_PRESSED;
        last |= LEFT_BUTTON;

    } else if ((button_presses ^ last) == RIGHT_BUTTON && !(last & RIGHT_BUTTON)) {
        event.type = RB_PRESSED;
        last |= RIGHT_BUTTON;

    } else if ((button_presses ^ last) == LEFT_BUTTON && (last & LEFT_BUTTON)) {
        event.type = LB_RELEASED;
        last &= ~LEFT_BUTTON;

    } else if ((button_presses ^ last) == RIGHT_BUTTON && (last & RIGHT_BUTTON)) {
        event.type = RB_RELEASED;
        last &= ~RIGHT_BUTTON;

    } else if ((delta_x || delta_y) && (button_presses == last)) {
        event.type = MOUSE_MOV;

    } else
        event.type = BUTTON_EV;

    event.delta_x = delta_x;
    event.delta_y = delta_y;
    return &event;
}
*/

int mouse_check_pattern(struct mouse_ev evt, uint8_t x_len) {
  static state_t pattern_state = INIT; // initial state; keep state
  static int lineXLen = 0; // line movement in X
  switch (pattern_state) {
    case INIT:
      if ((evt.type == LB_PRESSED && evt.type != RB_PRESSED) || (evt.type == MOUSE_MOV && evt.type == LB_PRESSED && evt.type != RB_PRESSED)
      ){
        lineXLen = 0;
        pattern_state = DRAW_UP;
      } //else we stay on INIT
      break;
    case DRAW_UP:
      if (evt.type == MOUSE_MOV) {
        lineXLen += evt.delta_x;
        if (evt.type != LB_PRESSED && evt.type == RB_PRESSED && lineXLen >= x_len) { // although a move type, we allow the button change
          pattern_state = DRAW_DOWN;
        }
        else if (evt.delta_x <= 0 || evt.delta_y <= 0 || (evt.delta_y / evt.delta_x) < MIN_SLOPE || evt.type != LB_PRESSED || (evt.type == RB_PRESSED && lineXLen < x_len)) { // note that lifting left button and pressing right is handled before
          pattern_state = INIT;
        }
      } // evt.type == MOVE
      else if (evt.type == RB_PRESSED) { // change the line draw
        if (evt.type != LB_PRESSED && // it was a right click, but we're extra careful
        evt.type == RB_PRESSED && lineXLen >= x_len) {
          lineXLen = 0;
          pattern_state = DRAW_DOWN;
        }
        else { // does not comply, right click with other buttons or length of UP too short
          pattern_state = INIT;
        }
      } // evt.type == RBDOWN
      else { // other event type goes to restart
        pattern_state = INIT;
      }
      break; // from case DRAW_UP
    case DRAW_DOWN:
      if (evt.type == MOUSE_MOV){
        lineXLen += evt.delta_x;
        if (evt.type != RB_PRESSED || evt.type == LB_PRESSED || (evt.delta_y / evt.delta_x) >= -MIN_SLOPE){
          pattern_state = INIT;
        }
        else if (lineXLen >= x_len){
          pattern_state = DETECTED;
        }
      }
      else { // other event type goes to restart
        pattern_state = INIT;
      }
      break;
    case DETECTED:
      return 0;
    default:
      return 1;
  }
  return 1;
}
