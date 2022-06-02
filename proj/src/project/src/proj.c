#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
#include <lcom/proj.h>

#include "libs.h"
#include "game.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/src/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/src/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(proj_main_loop)(int argc, char* argv[])
{
  (void)argc; (void)argv;
  uint16_t mode = INDEXED_1024_768;
  
  if(set_graphics_mode(mode)) return 1;

  if(map_vram(mode)) return 1;

  if(mainLoop()) return 1;

  if(vg_exit()) return 1;

  return OK;
}

