#include <lcom/lcf.h>

#include "rtc.h"

#include "utils.h"

int hook_id_rtc = 8;
struct time_struct *time_s;
struct date_struct *date_s;

int (rtc_subscribe_int)(uint8_t *bit_no) {
  *bit_no = hook_id_rtc;
  rtc_set_updates(false);
  return sys_irqsetpolicy(RTC_IRQ, (IRQ_REENABLE | IRQ_EXCLUSIVE), &hook_id_rtc);
}

int (rtc_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_id_rtc) != 0;
}

int (rtc_read_register)(uint32_t reg, uint8_t *data) {
    if (sys_outb(RTC_ADDR_REG, reg)) return 1;

    if (util_sys_inb(RTC_DATA_REG, data)) return 1;

    return 0;
}

int (rtc_write_register)(uint32_t reg, uint8_t data) {
    if (sys_outb(RTC_ADDR_REG, reg)) return 1;

    if (sys_outb(RTC_DATA_REG, data)) return 1;

    return 0;
}

int (rtc_check_update)() {
  uint8_t data;

  if (rtc_read_register(RTC_REG_A, &data)) return 1;

  return (data & UIP) != 0;
}

int rtc_set_updates(bool enable) {
  uint32_t regB;

  if (sys_outb(RTC_ADDR_REG, RTC_REG_B) != 0) return 1;
  if (sys_inb(RTC_DATA_REG, &regB) != 0) return 1;

  if (enable) {
    regB = regB | SET;
  }
  else {
    regB = regB & ~SET;
  }

  if (sys_outb(RTC_ADDR_REG, RTC_REG_B) != 0) return 1;
  if (sys_outb(RTC_DATA_REG, regB) != 0) return 1;

  return 0;
}

int (rtc_read_time)(struct time_struct *t) {
  if(rtc_set_updates(true)) return 1;

  if(rtc_read_sec(&t->sec)) return 1;
  if(rtc_read_min(&t->min)) return 1;
  if(rtc_read_hour(&t->hour)) return 1;

  if(rtc_set_updates(false)) return 1;

  return 0;
}

int (rtc_read_date)(struct date_struct *d) {
  if(rtc_check_update()) return 1;

  if(rtc_set_updates(true)) return 1;

  if(rtc_read_weekday(&d->weekday)) return 1;
  if(rtc_read_day(&d->day)) return 1;
  if(rtc_read_month(&d->month)) return 1;
  if(rtc_read_year(&d->year)) return 1;

  if(rtc_set_updates(false)) return 1;

  return 0;
}

int (rtc_read_sec)(uint8_t *sec) {
    return rtc_read_register(RTC_SEC, sec);
}

int (rtc_read_min)(uint8_t *min) {
    return rtc_read_register(RTC_MIN, min);
}

int (rtc_read_hour)(uint8_t *hour) {
    return rtc_read_register(RTC_HOUR, hour);
}
  
int (rtc_read_weekday)(uint8_t *weekday) {
    return rtc_read_register(RTC_WEEK_DAY, weekday);
}

int (rtc_read_day)(uint8_t *day) {
    return rtc_read_register(RTC_MONTH_DAY, day);
}

int (rtc_read_month)(uint8_t *month) {
    return rtc_read_register(RTC_MONTH, month);
}

int (rtc_read_year)(uint8_t *year) {
    return rtc_read_register(RTC_YEAR, year);
}

void rtc_ih() {
  uint8_t data;

  if (rtc_read_register(RTC_REG_C, &data)) return;

  if (data & UF) {
    if(rtc_read_time(time_s)) return;
    if(rtc_read_date(date_s)) return;
  }
}
