#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include "i8254.h"


int (timer_subscribe_int)(uint8_t *bit_no);

int (timer_unsubscribe_int)();

void (timer_int_handler)();

void (timer_reset_no_interrupts)();

uint32_t (timer_get_no_interrupts)();

#endif
