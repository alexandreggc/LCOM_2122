// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

#include "videocard.h"
#include "timer.c"
#include "keyboard.c"
#include "utils.c"
#include "graphics_card_macros.h"


// Any header files included below this line should have been created by you

extern uint8_t bb[];
extern bool two_byte;
extern int size;
extern int kbd_error;
uint8_t kbc_cmd_byte=0;

extern uint32_t no_interrupts;

extern void *video_mem;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {
  set_graphics_mode(mode);
  sleep(delay);
  //tickdelay(micros_to_ticks(delay*1000000));
  vg_exit();
  return OK;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,uint16_t width, uint16_t height, uint32_t color) {
  map_vram(mode);
  set_graphics_mode(mode);
  vg_draw_rectangle(x,y,width,height,color);
  
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
         if(keyboard_check_esc(bb))
            process=0;
     } else { /* received a standard message, not a notification */
         /* no standard messages expected: do nothing */
     }
  }
  kbd_unsubscribe_int();
  vg_exit();
  return OK;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  /* To be completed */
  printf("%s(0x%03x, %u, 0x%08x, %d): under construction\n", __func__,
         mode, no_rectangles, first, step);

  return 1;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  xpm_image_t img;
  uint8_t *map;
  in_port_t mode = INDEXED_1024_768;

  map_vram(mode);
  set_graphics_mode(mode);

  map = xpm_load(xpm, XPM_INDEXED, &img);
  img.bytes = map;
  vg_draw_xpm_img(&img, x, y);

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
         if(keyboard_check_esc(bb))
            process=0;
     } else { /* received a standard message, not a notification */
         /* no standard messages expected: do nothing */
     }
  }
  kbd_unsubscribe_int();
  vg_exit();

  return OK;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf, int16_t speed, uint8_t fr_rate) {
  xpm_image_t img;
  uint8_t *map;
  in_port_t mode = INDEXED_1024_768;

  map_vram(mode);
  set_graphics_mode(mode);

  map = xpm_load(xpm, XPM_INDEXED, &img);
  img.bytes = map;

  no_interrupts = 0;
  const uint32_t frequency = 60;
  int ipc_status, r;
  uint8_t keyboard_sel;
  uint8_t timer_sel;
  message msg;
  bool make;

  if(kbd_subscribe_int(&keyboard_sel))
    return 1;
  if(timer_subscribe_int(&timer_sel))
    return 1;
  
  int timer_irq = BIT(timer_sel);
  int kbd_irq = BIT(keyboard_sel);
  int process = 1;

  int16_t v = (speed <= 0 ? 1 : speed);
  int16_t vx = 0, vy = 0;
  if(xi != xf){
    vx = (xi < xf ? v : -v);
  }else{
    vy = (yi < yf ? v : -v);
  }
  int x = xi, y = yi;

  uint16_t frames_to_move_onepx  = (speed <  0 ? -speed : 1);
  uint32_t ticks_per_frame = frequency/(uint32_t)fr_rate;
  vg_draw_xpm_img(&img, x, y);

  while( process ) { /* You may want to use a different condition */
     /* Get a request message. */
     if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
         printf("driver_receive failed with: %d", r);
         continue;
     }
     if (is_ipc_notify(ipc_status)) { /* received notification */
         switch (_ENDPOINT_P(msg.m_source)) {
             case HARDWARE: /* hardware interrupt notification */ 
                if (msg.m_notify.interrupts & timer_irq) { /* subscribed interrupt */
                      timer_int_handler();/* process it */
                      if (no_interrupts == frames_to_move_onepx*ticks_per_frame){
                        vg_clear_screen();

                        vx = (vx > 0 ? min(vx, xf-x) : max(vx, xf-x) );
                        vy = (vy > 0 ? min(vy, yf-y) : max(vy, yf-y) );
                        x += vx;
                        y += vy;

                        vg_draw_xpm_img(&img, x, y);
                        no_interrupts = 0;
                      }
                 }     
                 if (msg.m_notify.interrupts & kbd_irq) { /* subscribed interrupt */
                      kbc_ih();/* process it */
                      if(two_byte || kbd_error){
                        continue;
                      }
                      keyboard_get_code(&make, bb);
                      if(keyboard_check_esc(bb)) process=0;
                 }
                 break;
             default:
                 break; /* no other notifications expected: do nothing */ 
         }
     } else { /* received a standard message, not a notification */
         /* no standard messages expected: do nothing */
     }
  }
  timer_unsubscribe_int();
  kbd_unsubscribe_int();
  vg_exit();

  return OK;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}
