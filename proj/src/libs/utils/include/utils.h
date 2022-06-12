#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

/**
 * @defgroup utils utils
 * @ingroup libs
 * @{
 */
/**
 * Get least significant byte of the val argument
 * @param val original value 16bit
 * @param lsb least significant byte of the val
 * @return 0 if success or 1 otherwise
 */
int(util_get_LSB)(uint16_t val, uint8_t *lsb);
/**
 * Get most significant byte of the val argument
 * @param val original value 16bit
 * @param msb most significant byte of the val
 * @return 0 if success or 1 otherwise
 */
int(util_get_MSB)(uint16_t val, uint8_t *msb);

#ifdef LAB3
   int getCounter();
#endif

/**
 * Get 8bit value from the argument's port
 * @param port the port
 * @param value address to store the value read from the port
 * @return 0 if success or 1 otherwise
 */
int (util_sys_inb)(int port, uint8_t *value);
/**
 * Get the higher value between the two arguments
 * @param a 16bit value
 * @param b 16bit value
 * @return the higher value
 */
int16_t max_16(int16_t a, int16_t b);
/**
 * Get the lower value between the two arguments
 * @param a 16bit value
 * @param b 16bit value
 * @return the lower value
 */
int16_t min_16(int16_t a, int16_t b);

#define BCD_FIRST(n)     (n >> 4)
#define BCD_SECOND(n)    (n & 0x0F)

/**
 * @}
 */
#endif //UTILS_H_INCLUDED
