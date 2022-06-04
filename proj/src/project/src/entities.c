#include<lcom/lcf.h>
#include "libs.h"
#include "entities.h"

#define MAP_BLOCKS 20
#define BLOCK_PX_SIZE  30


struct map{
  sprite_t* background;
  uint8_t* elements;
  int x, y;
  int w, h;
  int size;
};

map_t* (map_constructor)(const char *const *xpm){
  enum element_t ele;
  map_t* map = malloc(sizeof(map_t));
  sprite_t* sp = sprite_constructor(xpm);
  map->h = sprite_get_height(sp)/BLOCK_PX_SIZE;
  map->w = sprite_get_width(sp)/BLOCK_PX_SIZE;
  map->size = map->h * map->w;
  uint8_t* el = malloc(sizeof(ele)*map->size);
  map->elements = el;
  (void)ele;
  return map;
}


void (map_destructor)(map_t *map){
  if (map == NULL) return;
  sprite_destructor(map->background);
  free(map->elements);
}
