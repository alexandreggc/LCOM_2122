#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

#include "i8254.h"
#include "keyboard_macros.h"
#include "utils.h"
#include "sprite.h"
#include "project_macros.h"
#include "keys.h"

int (kbd_get_size_bb)();
int (kbd_subscribe_int)(uint8_t *bit_no);
int (kbd_unsubscribe_int)();

void (keyboard_get_code)(bool *make, uint8_t bbyte[2]);
int (keyboard_process_key)(uint8_t bbyte[2], sprite_t* sp);
int(kbd_enable_int)();
int (kbd_write_command)(uint8_t kbc_cmd, uint8_t arg, bool has_arg);
int (kbd_read_outbuf)(uint8_t *data);
void (process_scancode)(uint8_t value);
void (kbd_polling)();
void (reset_vars)();
int is_two_byte();
int kbd_error_occured(); 
void keyboard_get_key(uint8_t *key);
int (kbd_process_key)(uint8_t bbyte[2], keys_t *keys);
int (keyboard_check_esc)(uint8_t bb[2]);


#endif 
