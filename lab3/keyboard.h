#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

uint8_t bb[2];
uint8_t two_byte;

void (keyboard_get_code)(bool *make, uint8_t bb[2]);
int (keyboard_check_esc)(uint8_t bb[2]);
int(kbd_enable_int)();

#endif 
