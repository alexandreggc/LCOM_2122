#ifndef RTC_H_INCLUDED
#define RTC_H_INCLUDED

#include <lcom/lcf.h>
#include <stdint.h>
#include "rtc_macros.h"

/**
 * @defgroup rtc rtc
 * @ingroup libs
 *
 * @{
 */

struct date_struct {
  uint8_t weekday;
  uint8_t day;
  uint8_t month;
  uint8_t year;
};

struct time_struct {
  uint8_t sec;
  uint8_t min;
  uint8_t hour;
};
/**
 * Subscribes rtc interrupts
 * @param bit_no bit of the interrupts vector that will be set when rtc interrupts
 * @return 0 if success of 1 otherwise
 */
int (rtc_subscribe_int)(uint8_t *bit_no);
/**
 * Unsubscribes rtc interrupts
 * @return 0 if success of 1 otherwise
 */
int (rtc_unsubscribe_int)();
/**
 * Read rtc register
 * @param reg register to be read from
 * @param data address to store the read date
 * @return 0 if success of 1 otherwise
 */
int (rtc_read_register)(uint32_t reg, uint8_t *data);
/**
 * Write rtc register
 * @param reg register to write data
 * @param data data to be written
 * @return 0 if success of 1 otherwise
 */
int (rtc_write_register)(uint32_t reg, uint8_t data);
/**
 * Reads seconds register
 * @param sec address to store the seconds
 * @return 0 if success of 1 otherwise
 */
int (rtc_read_sec)(uint8_t *sec);
/**
 * Read minutes register
 * @param min address to store the minutes
 * @return 0 if success of 1 otherwise
 */
int (rtc_read_min)(uint8_t *min);
/**
 * Read the hours register
 * @param hour address to store the hours
 * @return 0 if success of 1 otherwise
 */
int (rtc_read_hour)(uint8_t *hour);
/**
 * Read the weekday register
 * @param weekday address to store the weekday
 * @return 0 if success of 1 otherwise
 */
int (rtc_read_weekday)(uint8_t *weekday);
/**
 * Read the day register
 * @param day address to store the day
 * @return 0 if success of 1 otherwise
 */
int (rtc_read_day)(uint8_t *day);
/**
 * Read the month register
 * @param month address to store the month
 * @return 0 if success of 1 otherwise
 */
int (rtc_read_month)(uint8_t *month);
/**
 * Read the year register
 * @param year address to store the year
 * @return 0 if success of 1 otherwise
 */
int (rtc_read_year)(uint8_t *year);
/**
 * Updated the global struct of time and date with new values
 * @return 0 if success of 1 otherwise
 */
int (rtc_check_update)();
/**
 * Rtc interrupt handler
 */
void (rtc_ih)();
/**
 * Read all timer values from the rtc registers and store them in time struct
 * @param t address of the time struct to store the data
 * @return 0 if success of 1 otherwise
 */
int (rtc_read_time)(struct time_struct *t);
/**
 * Read all date values from the rtc registers and store them in date struct
 * @param d address of the time struct to store the data
 * @return 0 if success of 1 otherwise
 */
int (rtc_read_date)(struct date_struct *d);
/**
 * Enables/Disables interrupts on update
 * @param enable 0 to disable, any other value to enable
 * @return 0 if success of 1 otherwise
 */
int (rtc_set_updates)(bool enable);
/**
 * Get a c string with the current date and time
 * @return 0 if success of 1 otherwise
 */
char* (rtc_get_real_time());
/**
 * Updated with date and time structs with real time
 */
void(rtc_update_real_time)();
/**
 * Reads date from register and stores it in the argument address
 * @param string address to store the c string
 */
void (rtc_get_date)(char* string);

/**
 * @}
 */

#endif /* end of include guard: RTC_H_INCLUDED */
