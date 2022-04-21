#ifndef _LCOM_keyboard_macros_H_
#define _LCOM_keyboard_macros_H_

#include <lcom/lcf.h>

#define KB_IRQ 1 /**< @brief Keyboard IRQ line */

#define OUT_BUF 0x60
#define TWO_BYTE_CODE 0xE0

#define ESC_CODE  0x81

#define STATUS_REG_ERR 0x2

#define STAT_REG 0x64
#define CMD_REG 0x64

#define READ_CMD_BYTE 0x20
#define WRITE_CMD_BYTE 0X60

#define WRITE_KBC 0x60

#define IBF_FULL BIT(1)
#define OBF_FULL BIT(0)
#define KBC_PAR_ERR BIT(7)
#define KBC_TO_ERR BIT(6)

#define DELAY_US 20000

#define KBC_ENABLE_INT BIT(0)




#endif
