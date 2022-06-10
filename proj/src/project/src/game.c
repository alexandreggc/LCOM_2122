#include "game.h"
#include "libs.h"
#include "entities.h"
#include "crosshair.xpm"
#include "font.h"


extern int no_interrupts;

int(mainLoop)(){  
  enum GameState gameState = MENU;
  int bombsUsed = 0;
  player_t *player = player_constructor(195, 85);
  bot_t** bots = malloc(sizeof(bot_t*)*NUMBER_OF_BOTS);
  bomb_t** bombs = malloc(sizeof(bomb_t*)*NUMBER_OF_BOMBS);
  sprite_t *mouse = sprite_constructor((const char* const*)crosshair_xpm);
  map_t* map = map_constructor();
  bomb_populate(bombs);
  map_place_bots(map,bots);
  sprite_set_pos(mouse, 100, 100);
  sprite_draw(mouse);

  font_t *font = font_ctor(NUM_SYMBOLS);
 
  int ipc_status, r;
  uint8_t keyboard_sel;
  message msg;  

  menu_t *main_menu = menu_ctor(font, 2);
  menu_add_button(main_menu, 200, 200, 400, 100, "PLAY THE GAME");
  menu_add_button(main_menu, 200, 400, 350, 150, "EXIT");

  if(kbd_subscribe_int(&keyboard_sel))
    return 1;
  int kbc_irq_set = BIT(keyboard_sel);

  uint8_t timer_sel;

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
  struct packet pp;
  int keyboard_refresh = 1;
  keys_t *curr_keys = keys_ctor();

  while(gameState != EXIT){
      int mouse_refresh = 1;
      while( gameState == MENU ) { /* You may want to use a different condition */
     /* Get a request message. */
     if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
         printf("driver_receive failed with: %d", r);
         continue;
     }
     if (is_ipc_notify(ipc_status)) { /* received notification */
         switch (_ENDPOINT_P(msg.m_source)) {
             case HARDWARE: /* hardware interrupt notification */       
                 if (msg.m_notify.interrupts & timer_irq_set) { /* subscribed interrupt */
                     timer_int_handler();   /* process it */
                     if((timer_get_no_interrupts()) % (sys_hz()/REFRESH_RATE) == 0){ // atualiza a cada 1 segundo
                        timer_reset_no_interrupts();
                        if(mouse_refresh){
                          vg_clear_screen();
                          menu_draw(main_menu);
                          sprite_set_speed(mouse, get_mouse_x_speed(), get_mouse_y_speed());
                          sprite_update_pos(mouse);
                          reset_mouse_speed();
                          mouse_refresh = 0;
                          sprite_draw(mouse);
                          vg_draw();
                        }      
                 }
                 }
                 if (msg.m_notify.interrupts & mouse_irq_set) { /* subscribed interrupt */
                      mouse_ih();
                      if(get_ih_counter() >= 3){
                          mouse_parse_packet(&pp);           
                          mouse_refresh = update_mouse(&pp);
                          if(mouse_refresh){
                            switch (menu_update_state(main_menu, mouse, pp.lb)){
                              case 1: {
                                gameState = PLAY;
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
                 if (msg.m_notify.interrupts & kbc_irq_set) { /* subscribed interrupt */
                      kbc_ih();/* process it */
                      if(is_two_byte() || kbd_error_occured()){
                        continue;
                      }
                      uint8_t bb[2];
                      keyboard_get_key(bb);
                      if(keyboard_check_esc(bb))
                        gameState = EXIT;
                     
                 }
                 break;
             default:
                 break; /* no other notifications expected: do nothing */ 
         }
     } else { /* received a standard message, not a notification */
         /* no standard messages expected: do nothing */
     }
  }

  while( gameState == PLAY) { /* You may want to use a different condition */
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
                      if(player_process_key(bb, kbd_get_size_bb(), curr_keys)){
                          gameState = MENU;
                        }
                      else
                        keyboard_refresh = 1;
                     
                 }
                 if (msg.m_notify.interrupts & timer_irq_set) { /* subscribed interrupt */
                  timer_int_handler();   /* process it */
                  if((timer_get_no_interrupts() * 60) % REFRESH_RATE == 0){
                  timer_reset_no_interrupts();
                  vg_clear_screen();
                  for(int i=0; i<NUMBER_OF_BOTS; i++) {
                    map_update_bot_grid(map,bots[i]);
                    map_test_bot_collisions(map,bots[i]);
                    bot_move(bots[i]);
                    bot_draw(bots[i]);
                  }
                  map_update_player_grid(map, player);     
                  if(mouse_refresh){
                    sprite_set_speed(mouse, get_mouse_x_speed(), get_mouse_y_speed());
                    sprite_update_pos(mouse);
                    reset_mouse_speed();
                    mouse_refresh = 0;
                  }
                  if(keyboard_refresh){
                    player_set_speed(player, curr_keys);
                    map_test_collisions(map, player);
                    //keyboard_refresh = 0;
                    if(bombsUsed<NUMBER_OF_BOMBS) {
                      player_check_place_bomb(player, curr_keys, bombs[bombsUsed], &bombsUsed);
                    }
                  } 
                  map_draw(map);
                  bomb_draw(bombs);
                  player_draw(player);
                  sprite_draw(mouse);
                  vg_draw();
                  }
                }
                 if (msg.m_notify.interrupts & mouse_irq_set) { /* subscribed interrupt */
                      mouse_ih();
                      if(get_ih_counter() >= 3){
                          mouse_parse_packet(&pp);           
                          if((mouse_refresh = update_mouse(&pp)) == 1)
                            check_bomb_click(bombs, mouse, pp.lb);
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
  map_destructor(map);
  player_destructor(player);
  bot_destructor(bots);
  bomb_destructor(bombs);
  sprite_destructor(mouse);
  font_dtor(font);
  menu_dtor(main_menu);
  keys_dtor(curr_keys);

  return OK;
}
