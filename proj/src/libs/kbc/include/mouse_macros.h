#ifndef MOUSE_MACROS_H_INCLUDED
#define MOUSE_MACROS_H_INCLUDED

#include <lcom/lcf.h>
/**
 * @defgroup mouse mouse
 * @ingroup kbc
 * @{
 */
#define IRQ_LINE 12
#define STAT_REG 0x64
#define CTRL_REG 0x64
#define IN_BUF 0x60
#define OUT_BUF 0x60
#define SUC_BYTE 0xFA
#define ERR_BYTE 0xFE


#define Y_OVFL BIT(7)
#define X_OVFL BIT(6)
#define Y_SIGN BIT(5)
#define X_SIGN BIT(4)
#define FIRST_BYTE_ID BIT(3)
#define MIDDLE_BUTTON BIT(2)
#define RIGHT_BUTTON BIT(1)
#define LEFT_BUTTON BIT(0)

// Mouse commands
#define MOUSE_WRITE_CMD 0xD4

#define DISABLE_DATA_REPORT 0xF5
#define ENABLE_DATA_REPORT 0xF4

// Mouse responses
#define ACK 0xFA // if everything OK
#define NACK 0xFE // if invalid byte (may be due to a serial communication error)
#define ERROR 0xFC // second consecutive invalid byte
#define ACKS_DELAY 20000

/**
 * @}
 */
#endif // MOUSE_MACROS_H_INCLUDED
