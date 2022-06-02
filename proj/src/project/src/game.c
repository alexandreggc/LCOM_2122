#include "game.h"
#include "libs.h"

extern uint8_t bb[2];
extern bool two_byte;
extern int kbd_error;

int(mainLoop)(){
  int16_t x = 100, y = 70, width = 50, height = 50;
  uint32_t color = 3;
  
  vg_draw_rectangle(x,y,width,height,color);

  sprite_t *player = sprite_constructor((const char* const*)penguin);
  sprite_set_pos(player, 0, 0);
  sprite_draw(player);

  int ipc_status, r;
  uint8_t keyboard_sel;
  message msg;  
  bool make;

  if(kbd_subscribe_int(&keyboard_sel))
    return 1;
  int irq_set = BIT(keyboard_sel);
  int process = 1;

  while( process ) { /* You may want to use a different condition */
     /* Get a request message. */
     if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
         printf("driver_receive failed with: %d", r);
         continue;
     }
     if (is_ipc_notify(ipc_status)) { /* received notification */
         switch (_ENDPOINT_P(msg.m_source)) {
             case HARDWARE: /* hardware interrupt notification */       
                 if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
                      kbc_ih();/* process it */
                      if(two_byte || kbd_error){
                        continue;
                      }
                      keyboard_get_code(&make, bb);
                 }
                 break;
             default:
                 break; /* no other notifications expected: do nothing */ 
         }
         if(keyboard_check_esc(bb)) process=0;
     } else { /* received a standard message, not a notification */
         /* no standard messages expected: do nothing */
     }
  }

  kbd_unsubscribe_int();
  vg_exit();
  sprite_destructor(player);
  return OK;
}
