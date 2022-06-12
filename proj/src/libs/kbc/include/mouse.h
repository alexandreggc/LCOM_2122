#include <lcom/lcf.h>
#include "mouse_macros.h"
#include "keyboard_macros.h"
#include "keyboard.h"
#include "utils.h"
#include "videocard.h"

#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

/**
 * @defgroup mouse mouse
 * @ingroup kbc
 * @{
 */
/**
 * Subscribe mouse interrupts
 * @param bit_no bit of the interrupts vector that will be set when mouse interrupts
 * @return 0 if success or 1 otherwise
 */
int (mouse_subscribe_int)(uint8_t *bit_no);
/**
 * Unsubscribe mouse interrupts
 * @return 0 if success or 1 otherwise
 */
int (mouse_unsubscribe_int)();
/**
 * Mouse interrupt handler
 */
void (mouse_ih)();
/**
 * Parses read data from the kbc and stores it in given packet struct
 * @param pp address of the packet struct
 * @return 0 if success or 1 otherwise
 */
int (mouse_parse_packet)(struct packet *pp);
/**
 * Disable mouse interrupts temporally
 * @return 0 if success or 1 otherwise
 */
int (disable_irq());
/**
 * Enables mouse interrupts
 * @return 0 if success or 1 otherwise
 */
int (enable_irq());
/**
 * Disables mouse data reporting, writing to kbc the right command
 * @return 0 if success or 1 otherwise
 */
int (disable_data_reporting)();
/**
 * Write to mouse command to kbc
 * @param cmd mouse command
 * @return 0 if success or 1 otherwise
 */
int (mouse_issue_cmd)(uint8_t cmd);
/**
 * Read out buffer with mouse data
 * @param byte byte read from out buffer
 * @return 0 if success or 1 otherwise
 */
int (mouse_read_byte)(uint8_t *byte);
/**
 * Get interrupt counter value
 * @return 0 if success or 1 otherwise
 */
int (get_ih_counter)();
/**
 * Get mouse x speed value
 * @return mouse x speed
 */
int (get_mouse_x_speed)();
/**
 * Get mouse y speed value
 * @return mouse y speed
 */
int (get_mouse_y_speed)();
/**
 * Reset mouse speed
 */
void (reset_mouse_speed)();
/**
 * Updated mouse data given a packet
 * @param pp address of the packet
 * @return 0 if success or 1 otherwise
 */
int (update_mouse)(struct packet *pp);
/**
 * @}
 */
#endif
