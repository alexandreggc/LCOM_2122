#include <lcom/lcf.h>

#include "sprite.h"
#include <stdio.h>

struct sprite{
  int x, y; // current position
  int width, height; // dimensions
  int xspeed, yspeed; // current speed
  char *map; // the pixmap
};

sprite_t* sprite_constructor(){
  sprite_t* ret = malloc(sizeof(sprite_t));
  if (ret==NULL) return ret;
  return ret;
}
