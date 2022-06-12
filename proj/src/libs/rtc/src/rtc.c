#include <lcom/lcf.h>

#include "rtc.h"

#include "utils.h"

int hook_id_rtc = 8;
struct time_struct time_s;
struct date_struct date_s;

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
  do {
  if (rtc_read_register(RTC_REG_A, &data)) return 1;
  } while (data & UIP);

  return 0;
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
  /* uint8_t data;

  if (rtc_read_register(RTC_REG_C, &data)) return;

  if (data & UF) {
    if(rtc_read_time(&time_s)) return;
    if(rtc_read_date(&date_s)) return;
  } */
}

void (rtc_get_real_time(char *string)){
  char *aux = (char *)malloc(38 * sizeof(char));
    
  char *weekday = (char *)malloc(12 * sizeof(char));

  


  switch (date_s.weekday)
  {
  case 0: weekday = "SUNDAY, "; break;
  case 1: weekday = "MONDAY, "; break;
  case 2: weekday = "TUESDAY, "; break;
  case 3: weekday = "WEDNESDAY, "; break;
  case 4: weekday = "THURSDAY, "; break;
  case 5: weekday = "FRIDAY, "; break;
  case 6: weekday = "SATURDAY, "; break;
    break;
  }
   char *day = (char *)malloc(4 * sizeof(char));
   if((BCD_FIRST(date_s.day))*10     + BCD_SECOND(date_s.day) < 10){
    *day = '0';
    sprintf(day + 1,"%d", BCD_SECOND(date_s.day));

  }
  else{
    sprintf(day,"%d",(BCD_FIRST(date_s.day))*10     + BCD_SECOND(date_s.day));
  }
   strcat(day, "/");
  char *month = (char *)malloc(4 * sizeof(char));
  if((BCD_FIRST(date_s.month))*10     + BCD_SECOND(date_s.month) < 10){
    *month = '0';
    sprintf(month + 1,"%d", BCD_SECOND(date_s.month));

  }
  else{
    sprintf(month,"%d",(BCD_FIRST(date_s.month))*10     + BCD_SECOND(date_s.month));
  }
  strcat(month, "/");

  char *year = (char *)malloc(6 * sizeof(char));
  sprintf(year,"%d",2000 +(BCD_FIRST(date_s.year))*10     + BCD_SECOND(date_s.year));
  strcat(year, " ");


  char *hour = (char *)malloc(4 * sizeof(char));
  if((BCD_FIRST(time_s.hour))*10     + BCD_SECOND(time_s.hour) < 10){
    *hour = '0';
    sprintf(hour + 1,"%d", BCD_SECOND(time_s.hour));

  }
  else{
    sprintf(hour,"%d",(BCD_FIRST(time_s.hour))*10     + BCD_SECOND(time_s.hour));
  }
  *(hour + 2) = ':';

  char *minute = (char *)malloc(4 * sizeof(char));
  if((BCD_FIRST(time_s.min))*10     + BCD_SECOND(time_s.min) < 10){
    *minute = '0';
    sprintf(minute + 1,"%d", BCD_SECOND(time_s.min));

  }
  else{
    sprintf(minute,"%d",(BCD_FIRST(time_s.min))*10     + BCD_SECOND(time_s.min));
  }
  *(minute + 2) = ':';


  char *second = (char *)malloc(4 * sizeof(char));
  if((BCD_FIRST(time_s.sec))*10     + BCD_SECOND(time_s.sec) < 10){
    *second = '0';
    sprintf(second + 1,"%d", BCD_SECOND(time_s.sec));

  }
  else{
    sprintf(second,"%d",(BCD_FIRST(time_s.sec))*10     + BCD_SECOND(time_s.sec));
  }


 unsigned int const sz1  = strlen(weekday);
  unsigned int const sz2  = strlen(day);
  unsigned int const sz3  = strlen(month);
  unsigned int const sz4  = strlen(year);
  unsigned int const sz5  = strlen(hour);
  unsigned int const sz6  = strlen(minute);
  unsigned int const sz7  = strlen(second);
   



memcpy(aux , weekday  , sz1 );
memcpy(aux + sz1       , day  , sz2 );
memcpy(aux + sz1 + sz2       , month  , sz3 );
memcpy(aux + sz1 + sz2 + sz3      , year  , sz4 );
memcpy(aux + sz1 + sz2 + sz3 + sz4    , hour , sz5 );
memcpy(aux + sz1 + sz2 + sz3 + sz4 + sz5    , minute , sz6 );
memcpy(aux + sz1 + sz2 + sz3 + sz4 + sz5 + sz6, second , sz7);

aux[sz1 + sz2 + sz3 + sz4 + sz5 + sz6 + sz7] = '\0'; 

free(weekday);
free(day);
free(month);
free(year);
free(hour);
free(minute);
free(second);

memcpy(string, aux, sz1 + sz2 + sz3 + sz4 + sz5 + sz6 + sz7);
free(aux);
}

void (rtc_update_real_time)(){
  rtc_read_date(&date_s);
  rtc_read_time(&time_s);
}


void (rtc_get_date)(char* string){
  char *aux = (char *)malloc(38 * sizeof(char));

  char *day = (char *)malloc(4 * sizeof(char));
   if((BCD_FIRST(date_s.day))*10     + BCD_SECOND(date_s.day) < 10){
    *day = '0';
    sprintf(day + 1,"%d", BCD_SECOND(date_s.day));

  }
  else{
    sprintf(day,"%d",(BCD_FIRST(date_s.day))*10     + BCD_SECOND(date_s.day));
  }
  strcat(day, "/");
  char *month = (char *)malloc(4 * sizeof(char));
  if((BCD_FIRST(date_s.month))*10     + BCD_SECOND(date_s.month) < 10){
    *month = '0';
    sprintf(month + 1,"%d", BCD_SECOND(date_s.month));

  }
  else{
    sprintf(month,"%d",(BCD_FIRST(date_s.month))*10     + BCD_SECOND(date_s.month));
  }
  strcat(month, "/");

  char *year = (char *)malloc(6 * sizeof(char));
  sprintf(year,"%d",2000 +(BCD_FIRST(date_s.year))*10     + BCD_SECOND(date_s.year));
  strcat(year, " ");


  unsigned int const sz2  = strlen(day);
  unsigned int const sz3  = strlen(month);
  unsigned int const sz4  = strlen(year);


  memcpy(aux, day  , sz2 );
  memcpy(aux + sz2, month  , sz3 );
  memcpy(aux + sz2 + sz3, year  , sz4 );
  aux[sz2 + sz3 + sz4] = '\0'; 

  free(day);
  free(month);
  free(year);

  memcpy(string, aux, sz2 + sz3 + sz4);
  free(aux);
}

