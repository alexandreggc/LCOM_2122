#include<lcom/lcf.h>
#include "libs.h"
#include "entities.h"
#include "wall.xpm"
#include <math.h>

#define MAP_BLOCKS_SIZE 12

// WALL FUNCTIONS

struct wall{
  sprite_t* sp;
  int x_map, y_map;
  bool broken;
  bool steel;
};

wall_t* (wall_constructor)(int x, int y){
  wall_t* wall = malloc(sizeof(wall_t));
  sprite_t* sp = sprite_constructor((const char* const*)wall_xpm);
  wall->x_map = x;
  wall->y_map = y;
  wall->sp = sp;
  wall->broken = false;
  if (x==0 || y==0 || x==MAP_BLOCKS_SIZE-1 || y==MAP_BLOCKS_SIZE-1){
    wall->steel = true;
  }else{ wall->steel = false; }
  return wall;
}

void (wall_destructor)(wall_t* wall){
  if (wall == NULL) return;
  sprite_destructor(wall->sp);
  free(wall);
}

void (wall_draw)(wall_t* w){
  if (!w->broken)sprite_draw(w->sp);
}

bool (wall_broken)(wall_t* w){
  return w->broken;
}

int (wall_get_xmap)(wall_t* w){
  return w->x_map;
}

int (wall_get_ymap)(wall_t* w){
  return w->y_map;
}

void (wall_set_broken)(wall_t* w){
  if (!w->steel) w->broken = true;
}


// MAP FUNCTIONS

struct map{
  sprite_t* background;
  wall_t** walls;
  uint8_t* elements;
  int w_map, h_map;
  int size_map;
};

map_t* (map_constructor)(const char *const *xpm){
  int map_x = 150; int map_y = 40;
  //enum element_t ele;
  map_t* map = malloc(sizeof(map_t));
  wall_t** walls = malloc(sizeof(wall_t*)*MAP_BLOCKS_SIZE*MAP_BLOCKS_SIZE);
  for (int i=0; i<MAP_BLOCKS_SIZE*MAP_BLOCKS_SIZE; i++){
    walls[i] = malloc(sizeof(wall_t));
  }
  sprite_t* map_sp = sprite_constructor(xpm);
  sprite_set_pos(map_sp, map_x, map_y);
  wall_t* wall = wall_constructor(0,0);
  //uint8_t* el = malloc(sizeof(ele)*map->size_map);
  map->h_map = MAP_BLOCKS_SIZE;
  map->w_map = MAP_BLOCKS_SIZE;
  map->size_map = map->h_map * map->w_map;
  map->background = map_sp;
  map->elements = NULL;
  int wall_pixel_w = sprite_get_width(wall->sp);
  int wall_pixel_h = sprite_get_height(wall->sp);
  wall_destructor(wall);
  for (int j=0; j<MAP_BLOCKS_SIZE; j++){
    for (int i=0; i<MAP_BLOCKS_SIZE; i++){
      wall = wall_constructor(i, j);
      int wall_pixel_x = i*wall_pixel_w;
      int wall_pixel_y = j*wall_pixel_h;
      sprite_set_pos(wall->sp, map_x + wall_pixel_x, map_y + wall_pixel_y);
      if (rand() & 1){
        wall_set_broken(wall);
      }
      walls[i+j*map->w_map] = wall;
    }
  }
  map->walls = walls;
  //(void)ele;
  return map;
}


void (map_destructor)(map_t *map){
  if (map == NULL) return;
  sprite_destructor(map->background);
  for (int pos = 0; pos < MAP_BLOCKS_SIZE*MAP_BLOCKS_SIZE; pos++){
    wall_destructor(map->walls[pos]);
  }
  free(map->elements);
  free(map);
}

void (map_draw)(map_t *map){
  //sprite_draw(map->background);
  for (int j=0; j<MAP_BLOCKS_SIZE; j++){
    for (int i=0; i<MAP_BLOCKS_SIZE; i++){
      wall_t* wall = map->walls[i+j*map->w_map];
      wall_draw(wall);
    }
  }
}
