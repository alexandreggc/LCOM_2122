#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

uint8_t bb[2];
uint8_t two_byte;

void (keyboard_get_code)(bool *make, uint8_t bb[2]);
int (keyboard_check_esc)(uint8_t bb[2]);
int(kbd_enable_int)();
int (kbd_write_command)(uint8_t kbc_cmd, uint8_t arg, bool has_arg);
int (kbd_read_outbuf)(uint8_t *data);
void (process_scancode)(uint8_t value);
void (kbd_polling)();
void (reset_vars)();
#endif 
