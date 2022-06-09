#include <lcom/lcf.h>
#include "mouse_macros.h"
#include "keyboard_macros.h"
#include "keyboard.h"
#include "utils.h"
#include "videocard.h"

#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

int (mouse_subscribe_int)(uint8_t *bit_no);
int (mouse_unsubscribe_int)();
void (mouse_ih)();
int (mouse_parse_packet)(struct packet *pp);
int (disable_irq());
int (enable_irq());
int (disable_data_reporting)();
int (mouse_issue_cmd)(uint8_t cmd);
int (mouse_read_byte)(uint8_t *byte);
int (get_ih_counter)();

int (get_mouse_x_speed)();

int (get_mouse_y_speed)();

void (reset_mouse_speed)();


int (update_mouse)(struct packet *pp);
#endif 
