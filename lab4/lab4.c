// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include "mouse.h"
#include "keyboard.h"
#include "keyboard_macros.h"
#include "mouse_macros.h"

// Any header files included below this line should have been created by you

extern int mouse_ih_counter;
uint8_t kbc_cmd_byte=0;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (mouse_test_packet)(uint32_t cnt) {
    int ipc_status, r;
    message msg;
    uint8_t mouse_sel;
    uint32_t prints = 0;

    if(mouse_subscribe_int(&mouse_sel)){
        return 1;
    }
    if (disable_irq()) return 1;
    if(mouse_enable_data_reporting()) return 1;
    if (enable_irq()) return 1; // re-enables our interrupts notifications

    int mouse_irq = BIT(mouse_sel);
    int good = cnt != 0;
    mouse_ih_counter = 0;
    while (good) {
        /* Get a request message. */
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed with %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) { /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: /* hardware interrupt notification */
                    if (msg.m_notify.interrupts & mouse_irq) { /* subscribed interrupt */
                        mouse_ih();
                        if(mouse_ih_counter >= 3){
                            struct packet pp;
                            mouse_parse_packet(&pp);
                            mouse_print_packet(&pp);
                            prints++;
                            if(cnt == prints)
                                good = 0;
                        }
                    }
                    break;
                default:
                    break; /* no other notifications expected: do nothing */
            }
        } else { /* received standart message, not a notification */
            /* no standart message expected: do nothing */
        }
    }
    if (disable_irq()) return 1; // temporarily disables our interrupts notifications
    disable_data_reporting();
    uint8_t cmd_byte = minix_get_dflt_kbc_cmd_byte();
    kbd_write_command(WRITE_CMD_BYTE, cmd_byte, true);
    
    if (enable_irq()) return 1;
    if(mouse_unsubscribe_int()){
        return 1;
    }
    
    return OK;
}

int (mouse_test_async)(uint8_t idle_time) {
    /* To be completed */
    printf("%s(%u): under construction\n", __func__, idle_time);
    return 1;
}

int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerance){
    /* To be completed */
    printf("%s: under construction\n", __func__);
    return 1;
}

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
    /* This year you need not implement this. */
    printf("%s(%u, %u): under construction\n", __func__, period, cnt);
    return 1;
}
