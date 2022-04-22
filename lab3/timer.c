#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"
#include "time.h"

int hook_id = 0;
uint32_t no_interrupts = 0;


int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  if(freq > TIMER_FREQ || freq < TIMER_MIN_FREQ)
    return 1;
  uint8_t config, word_ctrl = 0;
  timer_get_conf(timer, &config);
  int timer_port;
  switch(timer){
    case 0: {
      word_ctrl = TIMER_SEL0; timer_port = TIMER_0; break;
    }
    case 1: {
      word_ctrl = TIMER_SEL1; timer_port = TIMER_1; break;
    }
    case 2: {
      word_ctrl = TIMER_SEL2; timer_port = TIMER_2; break;
    }
    default:
      return 1;
  }
  word_ctrl |= TIMER_LSB_MSB; 
  word_ctrl |= (config & 0x0f);
  sys_outb(TIMER_CTRL, word_ctrl);  

  uint16_t counter_init = (uint16_t)(TIMER_FREQ / freq);

  uint8_t lsb, msb;
  util_get_LSB(counter_init, &lsb);
  util_get_MSB(counter_init, &msb);

  sys_outb(timer_port, lsb);
  sys_outb(timer_port, msb);  

  return OK;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  *bit_no = hook_id;
  return sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id);
}

int (timer_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_id);
}

void (timer_int_handler)() {
  no_interrupts++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint8_t word_ctrl;
  int port;
  switch(timer){
    case 0: port = TIMER_0; break;
    case 1: port = TIMER_1; break;
    case 2: port = TIMER_2; break;
  }
  word_ctrl = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
  sys_outb(TIMER_CTRL, word_ctrl);
  util_sys_inb(port, st);
  return OK;
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  union timer_status_field_val conf;
  conf.byte = st;
  timer_print_config(timer, field, conf);
  return OK;
}
