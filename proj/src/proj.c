#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>

#include <lcom/proj.h>


#include "./defines/videocard.h"
#include "./defines/game.h"


int(proj_main_loop)(int argc, char* argv[])
{

  if(map_vram(DIRECT_800_600)) return 1;

  if(set_graphics_mode(DIRECT_800_600)) return 1;

  if(mainLoop()) return 1;

  if(vg_exit()) return 1;

  return OK;
}

