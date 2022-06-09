#ifndef _LCOM_keyboard_macros_H_
#define _LCOM_keyboard_macros_H_

#include <lcom/lcf.h>

#define KBC_NUM_TRIES 3
#define KB_IRQ 1 /**< @brief Keyboard IRQ line */

#define OUT_BUF 0x60
#define TWO_BYTE_CODE 0xE0

#define ESC_B_CODE  0x81
#define W_M_CODE  0x11
#define W_B_CODE  0x91
#define A_M_CODE  0x1E
#define A_B_CODE  0x9E
#define S_M_CODE  0x1F
#define S_B_CODE  0x9F
#define D_M_CODE  0x20
#define D_B_CODE  0xA0
#define ARROWUP_M_CODE  0xE048
#define ARROWUP_B_CODE  0xE0C8
#define ARROWLEFT_M_CODE  0xE04B
#define ARROWLEFT_B_CODE  0xE0CB
#define ARROWDOWN_M_CODE  0xE050
#define ARROWDOWN_B_CODE  0xE0D0
#define ARROWRIGHT_M_CODE  0xE04D
#define ARROWRIGHT_B_CODE  0xE0CD
#define SPACEBAR_M_CODE  0x39
#define SPACEBAR_B_CODE  0xB9



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
#define AUX_MOUSE BIT(5)

#define DELAY_US 20000

#define KBC_ENABLE_INT BIT(0)




#endif
