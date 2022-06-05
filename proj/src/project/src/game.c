#include "game.h"
#include "libs.h"
#include "bomberman.xpm"
#include "crosshair.xpm"
#include "font.h"

int(mainLoop)(){  
  enum GameState gameState = MENU;
  sprite_t *player = sprite_constructor((const char* const*)bomberman_xpm);
  sprite_t *mouse = sprite_constructor((const char* const*)crosshair_xpm);
  font_t *font = font_ctor(2);

  sprite_set_pos(mouse, 100, 100);

  int ipc_status, r;
  uint8_t keyboard_sel;
  message msg;  
  menu_t *main_menu = menu_ctor();
  if(kbd_subscribe_int(&keyboard_sel))
    return 1;
  int kbc_irq_set = BIT(keyboard_sel);

  uint8_t timer_sel;
  int no_interrupts = 0;

  if(timer_subscribe_int(&timer_sel))
    return 1;
  int timer_irq_set = BIT(timer_sel);

  uint8_t mouse_sel;
  if(mouse_subscribe_int(&mouse_sel))
    return 1;
  int mouse_irq_set = BIT(mouse_sel);

  if (disable_irq()) return 1;
  if(mouse_enable_data_reporting()) return 1;
  if (enable_irq()) return 1; // re-enables our interrupts notifications

  while( gameState != EXIT ) { /* You may want to use a different condition */
     /* Get a request message. */
     if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
         printf("driver_receive failed with: %d", r);
         continue;
     }
     if (is_ipc_notify(ipc_status)) { /* received notification */
         switch (_ENDPOINT_P(msg.m_source)) {
             case HARDWARE: /* hardware interrupt notification */       
                 if (msg.m_notify.interrupts & kbc_irq_set) { /* subscribed interrupt */
                      kbc_ih();/* process it */
                      if(is_two_byte() || kbd_error_occured()){
                        continue;
                      }
                      uint8_t bb[2];
                      keyboard_get_key(bb);
                      if(gameState == PLAY)
                        if(keyboard_process_key(bb, player))
                          gameState = EXIT;
                 }
                 if (msg.m_notify.interrupts & timer_irq_set) { /* subscribed interrupt */
                     timer_int_handler();   /* process it */
                     if((no_interrupts * 60) % REFRESH_RATE == 0){ // atualiza a cada 1 segundo
                        vg_clear_screen();
                        if(gameState == MENU){
                            menu_draw(main_menu);
                            font_draw_string(font, "ABBAAABA", 100, 50);
                        }
                        else if(gameState == PLAY)
                          sprite_draw(player);
                        sprite_draw(mouse);
                        no_interrupts = 0;
                        vg_draw();
                 }
                 }
                 if (msg.m_notify.interrupts & mouse_irq_set) { /* subscribed interrupt */
                      mouse_ih();
                      if(get_ih_counter() >= 3){
                          struct packet pp;
                          mouse_parse_packet(&pp);           
                          sprite_set_speed(mouse, pp.delta_x, pp.delta_y * UP);
                          sprite_update_pos(mouse);
                          if(gameState == MENU){
                            int state = menu_update_state(main_menu, mouse, pp.lb);
                            switch (state)
                            {
                            case 1: {
                              gameState = PLAY;
                              sprite_set_pos(player, 10, 10);
                              break;
                            }
                            case 2: {
                              gameState = EXIT;
                              break;
                            }
                            default:
                              break;
                            }
                          }

                      }
                 }
                 break;
             default:
                 break; /* no other notifications expected: do nothing */ 
         }
     } else { /* received a standard message, not a notification */
         /* no standard messages expected: do nothing */
     }
  }
  if(kbd_unsubscribe_int())
    return 1;
  if(timer_unsubscribe_int())
    return 1;


  if (disable_irq()) return 1; // temporarily disables our interrupts notifications
  disable_data_reporting();
  uint8_t cmd_byte = minix_get_dflt_kbc_cmd_byte();
  kbd_write_command(WRITE_CMD_BYTE, cmd_byte, true);
  
  if (enable_irq()) return 1;
  if(mouse_unsubscribe_int()){
      return 1;
  }
  vg_exit();
  sprite_destructor(player);
  sprite_destructor(mouse);
  font_dtor(font);
  menu_dtor(main_menu);

  return OK;
}
