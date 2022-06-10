#ifndef RTC_H_INCLUDED
#define RTC_H_INCLUDED

#include <lcom/lcf.h>
#include <stdint.h>
#include "rtc_macros.h"

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

int (rtc_subscribe_int)(uint8_t *bit_no);

int (rtc_unsubscribe_int)();

int (rtc_read_register)(uint32_t reg, uint8_t *data);

int (rtc_write_register)(uint32_t reg, uint8_t data);

int (rtc_read_sec)(uint8_t *sec);

int (rtc_read_min)(uint8_t *min);

int (rtc_read_hour)(uint8_t *hour);

int (rtc_read_weekday)(uint8_t *weekday);

int (rtc_read_day)(uint8_t *day);

int (rtc_read_month)(uint8_t *month);

int (rtc_read_year)(uint8_t *year);

int (rtc_check_update)();

void (rtc_ih)();

int (rtc_read_time)(struct time_struct *t);

int (rtc_read_date)(struct date_struct *d);

int (rtc_set_updates)(bool enable);

void (rtc_get_real_time(char *string));

void(rtc_update_real_time)();

#endif /* end of include guard: RTC_H_INCLUDED */
