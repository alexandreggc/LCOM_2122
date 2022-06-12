#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

#include "i8254.h"
#include "keyboard_macros.h"
#include "utils.h"
#include "sprite.h"
#include "project_macros.h"
#include "keys.h"
/**
 * @defgroup kbc kbc
 * @ingroup libs
 */
/**
 * @defgroup keyboard keyboard
 * @ingroup kbc
 * @{
 */

/**
 * Get the number of bytes of the current scan code that was read
 * @return number of bytes of the scan code
 */
int (kbd_get_size_bb)();
/**
 * Subscribe keyboard interrupts
 * @param bit_no bit of the interrupts vector that will be set when keyboard interrupts
 * @return 0 if success or 1 otherwise
 */
int (kbd_subscribe_int)(uint8_t *bit_no);
/**
 * Unsubscribe keyboard interrupts
 * @return 0 if success or 1 otherwise
 */
int (kbd_unsubscribe_int)();
/**
 * Check if the scan code is a break code or a make code
 * @param make address to store the boolean result
 * @param bbyte address of the array with the scan code
 */
void (keyboard_get_code)(bool *make, uint8_t bbyte[2]);
/**
 * Enable keyboard interrupts
 * @return 0 if success or 1 otherwise
 */
int(kbd_enable_int)();
/**
 * Write command to KBC
 * @param kbc_cmd kbc command byte
 * @param arg argument of the command byte
 * @param has_arg true if command byte has argument or false otherwise
 * @return 0 if success or 1 otherwise
 */
int (kbd_write_command)(uint8_t kbc_cmd, uint8_t arg, bool has_arg);
/**
 * Read out buffer of the kbc
 * @param data address to store data
 * @return 0 if success or 1 otherwise
 */
int (kbd_read_outbuf)(uint8_t *data);
/**
 * Process scan code bytes checking if it is a two byte scan code or not
 * @param value one byte of the scan code
 */
void (process_scancode)(uint8_t value);
/**
 * Polling function to read out buffer and process value read
 */
void (kbd_polling)();
/**
 * Reset keyboard global variables
 */
void (reset_vars)();
/**
 * Check if current read scan code has two byte
 * @return true if scan code with two bytes or false otherwise
 */
int is_two_byte();
/**
 * Get error code value
 * @return error code value
 */
int kbd_error_occured();
/**
 * Get the scan code of the key pressed
 * @param key address to store the scan code
 */
void keyboard_get_key(uint8_t *key);
/**
 * Process given scan code in the argument and updates the current pressed keys
 * @param bbyte array of the scan code
 * @param keys address of the keys struct
 * @return 0 is success or 1 otherwise
 */
int (kbd_process_key)(uint8_t bbyte[2], keys_t *keys);
/**
 * Check if the scan code passed in the argument if a ESC key break code
 * @param bb array of the scan code
 * @return 0 if success or 1 otherwise
 */
int (keyboard_check_esc)(uint8_t bb[2]);

/**
 * @}
 */
#endif 
