#include <lcom/lcf.h>
#include "mouse_macros.h"
#include "utils.h"

#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

int (mouse_subscribe_int)(uint8_t *bit_no);
int (mouse_unsubscribe_int)();
void (mouse_ih)();
int (mouse_parse_packet)(struct packet *pp);
int (disable_irq());
int (enable_irq());
#endif 
