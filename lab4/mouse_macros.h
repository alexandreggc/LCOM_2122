#ifndef MOUSE_MACROS_H_INCLUDED
#define MOUSE_MACROS_H_INCLUDED

#include <lcom/lcf.h>

#define IRQ_LINE 12
#define WRITE_CMD 0xD4
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
#define MIDDLE_BUTTON BIT(3)
#define RIGHT_BUTTON BIT(2)
#define LEFT_BUTTON BIT(1)




#endif // MOUSE_MACROS_H_INCLUDED
