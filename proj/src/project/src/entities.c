#include<lcom/lcf.h>
#include <math.h>

#include "project_functions.h"
#include "libs.h"
#include "entities.h"
#include "wall.xpm"
#include "bomberman.xpm"

#define MAP_BLOCKS_SIZE 12


//PLAYER FUNCTIONS

struct player{
  sprite_t* sp;
  int cx, cy, r;
  int x_map, y_map;
  int life;
};

player_t* (player_constructor)(int x, int y){
  player_t * ret = malloc(sizeof(player_t));
  sprite_t *sp = sprite_constructor((const char *const *)bomberman_xpm);
  sprite_set_pos(sp, x, y);
  ret->sp = sp;
  ret->x_map = 1;
  ret->y_map = 1;
  ret->r = sprite_get_width(sp)/2;
  ret->life = 1;
  return ret;
}

void (player_destructor)(player_t* p){
  sprite_destructor(p->sp);
  free(p);
}
void (player_draw)(player_t* p){
  sprite_draw(p->sp);
}
int (player_get_x)(player_t* p){
  return sprite_get_xpos(p->sp);
}
int (player_get_y)(player_t* p){
  return sprite_get_ypos(p->sp);
}
void (player_set_pos)(player_t* p, int x, int y){
  sprite_set_pos(p->sp, x, y);
}
int (player_get_mapx)(player_t* p){
  return p->x_map;
}
int (player_get_mapy)(player_t* p){
  return p->y_map;
}
void (player_set_map_pos)(player_t* p, int x, int y){
  p->x_map = x;
  p->y_map = y;
}
void (player_set_center)(player_t* p, int cx, int cy){
  p->cx = cx;
  p->cy = cy;
}

int (player_process_key)(uint8_t bbyte[2], int size, player_t* player){
  int h_dir = REST, v_dir = REST;
    if(size == 2){
      uint8_t lsb, msb;
      uint16_t arrowCodes[4] = {ARROWUP_CODE, ARROWLEFT_CODE, ARROWDOWN_CODE, ARROWRIGHT_CODE};
      for(uint8_t i = 0; i < 4; i++){
        util_get_LSB(arrowCodes[i], &lsb);
        util_get_MSB(arrowCodes[i], &msb);
        if(bbyte[0] == msb && bbyte[1] == lsb){
          switch (i){
          case 0:{
            v_dir = UP;
            break;
          }
          case 1:{
            h_dir = LEFT;
            break;
          }
          case 2:{
            v_dir = DOWN;
            break;
          }
          case 3:{
            h_dir = RIGHT;
            break;
          }
          default:
            break;
          }
          break;
        } 
      }
    }
  else{
    switch (bbyte[0])
    {
    case ESC_CODE: return 1;
    case W_CODE: {
      v_dir = UP;
      break;
      }
    case A_CODE: {
      h_dir = LEFT;
      break;
      }
      case S_CODE: {
        v_dir = DOWN;
        break;
      }
      case D_CODE: {
        h_dir = RIGHT;
        break;
      }
      case SPACEBAR_CODE: {
        break;
      }
    default:
      break;
    } 
  }

  sprite_set_speed(player->sp, h_dir * PLAYER_SPEED, v_dir * PLAYER_SPEED);
  return OK;
}



//BOT FUNCTIONS

struct bot{
  sprite_t* sp;
  int cx, cy, r;
  int x_map, y_map;
  int life;
};

bot_t* (bot_constructor)(int x, int y){
  bot_t * ret = malloc(sizeof(bot_t));
  sprite_t *sp = sprite_constructor((const char *const *)bomberman_xpm);
  sprite_set_pos(sp, x, y);
  ret->sp = sp;
  ret->x_map = 1;
  ret->y_map = 1;
  ret->r = sprite_get_width(sp)/2;
  ret->life = 1;
  return ret;
}

void (bot_destructor)(bot_t* p){
  sprite_destructor(p->sp);
  free(p);
}
void (bot_draw)(bot_t* p){
  sprite_draw(p->sp);
}
int (bot_get_x)(bot_t* p){
  return sprite_get_xpos(p->sp);
}
int (bot_get_y)(bot_t* p){
  return sprite_get_ypos(p->sp);
}
void (bot_set_pos)(bot_t* p, int x, int y){
  sprite_set_pos(p->sp, x, y);
}
int (bot_get_mapx)(bot_t* p){
  return p->x_map;
}
int (bot_get_mapy)(bot_t* p){
  return p->y_map;
}
void (bot_set_map_pos)(bot_t* p, int x, int y){
  p->x_map = x;
  p->y_map = y;
}
void (bot_set_center)(bot_t* p, int cx, int cy){
  p->cx = cx;
  p->cy = cy;
}

void (bot_move)(bot_t* bot) {
  int h_dir = REST, v_dir = REST;
  int xspeed = sprite_get_xspeed(bot->sp);
  int yspeed = sprite_get_yspeed(bot->sp);

  if(xspeed == 0 && yspeed == 0) {
    srand(time(NULL));
    int randomnumber = rand() % 4;
    switch(randomnumber) {
      case 0: h_dir = LEFT; break;
      case 1: h_dir = RIGHT; break;
      case 2: v_dir = UP; break;
      case 3: v_dir = DOWN; break;
      default: break;
    }
  } else if(xspeed != 0) {
    switch(xspeed) {
      case 1: h_dir = RIGHT; break;
      case -1: h_dir = LEFT; break;
    }
  } else if(yspeed != 0) {
    switch(yspeed) {
      case 1: v_dir = DOWN; break;
      case -1: v_dir = UP; break;
    }
  }

  sprite_set_speed(bot->sp, h_dir * BOT_SPEED, v_dir * BOT_SPEED);
}



// WALL FUNCTIONS

struct wall{
  sprite_t* sp;
  int x_map, y_map;
  int r;
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
  wall->r = sprite_get_width(sp)/2;
  if ((x==1&&y==1) || (x==2&&y==1) || (x==1&&y==2)) wall->broken = true;
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
  wall_t** walls;
  element_t* elements;
  int x,y;
  int w_map, h_map;
  int size_map;
};

map_t* (map_constructor)(){
  int map_x = 150; int map_y = 40;
  map_t* map = malloc(sizeof(map_t));
  wall_t** walls = malloc(sizeof(wall_t*)*MAP_BLOCKS_SIZE*MAP_BLOCKS_SIZE);
  for (int i=0; i<MAP_BLOCKS_SIZE*MAP_BLOCKS_SIZE; i++){
    walls[i] = malloc(sizeof(wall_t));
  }
  wall_t* wall = wall_constructor(0,0);
  element_t* el = malloc(sizeof(element_t)*map->size_map);
  map->x = map_x;
  map->y = map_y;
  map->h_map = MAP_BLOCKS_SIZE;
  map->w_map = MAP_BLOCKS_SIZE;
  map->size_map = map->h_map * map->w_map;
  map->elements = el;
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
  return map;
}


void (map_destructor)(map_t *map){
  if (map == NULL) return;
  for (int pos = 0; pos < map->size_map; pos++){
    wall_destructor(map->walls[pos]);
  }
  free(map->elements);
  free(map);
}

void (map_draw)(map_t *map){
  for (int j=0; j<MAP_BLOCKS_SIZE; j++){
    for (int i=0; i<MAP_BLOCKS_SIZE; i++){
      wall_t* wall = map->walls[i+j*map->w_map];
      wall_draw(wall);
    }
  }
}

void (map_update_player_grid)(map_t *map, player_t *player){
  int wall_px_w = sprite_get_width(map->walls[0]->sp);
  int wall_px_h = sprite_get_height(map->walls[0]->sp);
  int player_cx = player_get_x(player)+player->r;
  int player_cy = player_get_y(player)+player->r; 
  int player_xmap = (player_cx - map->x) / wall_px_w;
  int player_ymap = (player_cy - map->y) / wall_px_h;
  player_set_map_pos(player, player_xmap, player_ymap);
  player_set_center(player, player_cx, player_cy);
  //map->elements[player_xmap+player_ymap*map->w_map] = PLAYER;
}

void (map_update_bot_grid)(map_t *map, bot_t *bot){
  int wall_px_w = sprite_get_width(map->walls[0]->sp);
  int wall_px_h = sprite_get_height(map->walls[0]->sp);
  int bot_cx = bot_get_x(bot)+bot->r;
  int bot_cy = bot_get_y(bot)+bot->r; 
  int bot_xmap = (bot_cx - map->x) / wall_px_w;
  int bot_ymap = (bot_cy - map->y) / wall_px_h;
  bot_set_map_pos(bot, bot_xmap, bot_ymap);
  bot_set_center(bot, bot_cx, bot_cy);
}


void (map_test_collisions)(map_t *map, player_t *player){
  int xmap = player_get_mapx(player);
  int ymap = player_get_mapy(player);

  int index = xmap + (ymap*map->w_map);
  int index_UP = index - map->w_map;
  int index_DOWN = index + map->w_map;
  int index_RIGHT = index + 1;
  int index_LEFT = index - 1;
  int index_TOPLEFT = index_UP - 1;
  int index_TOPRIGHT = index_UP + 1;
  int index_BOTLEFT = index_DOWN - 1;
  int index_BOTRIGHT = index_DOWN + 1;
  int indexs[8] = {index_UP, index_DOWN, index_LEFT, index_RIGHT, index_TOPLEFT, index_TOPRIGHT, index_BOTLEFT, index_BOTRIGHT};
  for (int i=0; i<8; i++){
    wall_t * wall = map->walls[indexs[i]];
    int x0 = sprite_get_xpos(wall->sp)+wall->r;
    int y0 = sprite_get_ypos(wall->sp)+wall->r;
    int x = player->cx + sprite_get_xspeed(player->sp);
    int y = player->cy + sprite_get_yspeed(player->sp);
    if (point_distance(x0, y0, x, y) < (player->r+wall->r) && !wall_broken(wall)){
      sprite_set_speed(player->sp, 0, 0);
      break;
    }
  }
  sprite_update_pos(player->sp);
}


void (map_test_bot_collisions)(map_t *map, bot_t *bot){
  int xmap = bot_get_mapx(bot);
  int ymap = bot_get_mapy(bot);

  int index = xmap + (ymap*map->w_map);
  int index_UP = index - map->w_map;
  int index_DOWN = index + map->w_map;
  int index_RIGHT = index + 1;
  int index_LEFT = index - 1;
  int index_TOPLEFT = index_UP - 1;
  int index_TOPRIGHT = index_UP + 1;
  int index_BOTLEFT = index_DOWN - 1;
  int index_BOTRIGHT = index_DOWN + 1;
  int indexs[8] = {index_UP, index_DOWN, index_LEFT, index_RIGHT, index_TOPLEFT, index_TOPRIGHT, index_BOTLEFT, index_BOTRIGHT};
  for (int i=0; i<8; i++){
    wall_t * wall = map->walls[indexs[i]];
    int x0 = sprite_get_xpos(wall->sp)+wall->r;
    int y0 = sprite_get_ypos(wall->sp)+wall->r;
    int x = bot->cx + sprite_get_xspeed(bot->sp);
    int y = bot->cy + sprite_get_yspeed(bot->sp);
    if (point_distance(x0, y0, x, y) < (bot->r+wall->r) && !wall_broken(wall)){
      sprite_set_speed(bot->sp, 0, 0);
      break;
    }
  }
  sprite_update_pos(bot->sp);
}

