#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

/**
 * @defgroup timer timer
 * @ingroup libs
 * @{
 */
#include "i8254.h"

/**
 * Subscribes timer interrupts
 * @param bit_no bit of the interrupts vector that will be set when timer interrupts
 * @return 0 if success of 1 otherwise
 */
int (timer_subscribe_int)(uint8_t *bit_no);
/**
 * Unsubscribe timer interrupts
 * @return 0 if success of 1 otherwise
 */
int (timer_unsubscribe_int)();
/**
 * Timer interrupt handler
 */
void (timer_int_handler)();
/**
 * Resets the number of timer interrupts
 */
void (timer_reset_no_interrupts)();
/**
 * Get the number of timer interrupts
 * @return number of interrupts
 */
uint32_t (timer_get_no_interrupts)();

/**
 * @}
 */
#endif
