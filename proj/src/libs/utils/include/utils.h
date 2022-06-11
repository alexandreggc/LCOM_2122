#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

int(util_get_LSB)(uint16_t val, uint8_t *lsb);

int(util_get_MSB)(uint16_t val, uint8_t *msb);

#ifdef LAB3
   int getCounter();
#endif

int (util_sys_inb)(int port, uint8_t *value);

int16_t max_16(int16_t a, int16_t b);

int16_t min_16(int16_t a, int16_t b);

#define BCD_FIRST(n)     (n >> 4)
#define BCD_SECOND(n)    (n & 0x0F)

#endif //UTILS_H_INCLUDED
