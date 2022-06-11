#include<lcom/lcf.h>
#include "entities.h"
#include <math.h>
#include <stdio.h>

#include "libs.h"

#include "wall.xpm"
#include "bomberman.xpm"
#include "bomb.xpm"
#include "bomb2.xpm"
#include "stone.xpm"
#include "door.xpm"
#include "explosion.xpm"
#include "keys.h"


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

void (player_set_alive)(player_t *player){
  player->life = 1;
}

bool (player_alive)(player_t *player){
  return player->life;
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

void (player_set_speed)(player_t *player, keys_t *keys){
  sprite_set_speed(player->sp, (keys->right_pressed - keys->left_pressed) * PLAYER_SPEED, (keys->down_pressed - keys->up_pressed) * PLAYER_SPEED);
}

void (player_check_place_bomb)(map_t* map, player_t *player, keys_t *keys, bomb_t **bombs, int *bombsUsed){
  int new_x_map = player_get_mapx(player);
  int new_y_map = player_get_mapy(player);
  if(keys->space_pressed == 1){
    for (int i=0; i<NUMBER_OF_BOMBS; i++){
      bomb_t *b = bombs[i];
      int bomb_x_map = bomb_get_xmap(b);
      int bomb_y_map = bomb_get_ymap(b);
      if (bomb_x_map == new_x_map && bomb_y_map == new_y_map && !bomb_exploded(b)){
        return;
      }
    }
    for (int i=0; i<NUMBER_OF_BOMBS; i++){
      bomb_t *bomb = bombs[i];
      if (bomb_exploded(bomb)){
        map_place_bomb(map, bomb, new_x_map, new_y_map);
        (*bombsUsed)++;
        return;
      }
    }
  }
}

bool (player_test_exit_door)(player_t *player, door_t *door){
  int door_xmap = door_get_xmap_pos(door);
  int door_ymap = door_get_ymap_pos(door);
  return (player->x_map == door_xmap && player->y_map == door_ymap);
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

void (bot_destructor)(bot_t** bots){
  for(int i=0; i<NUMBER_OF_BOTS; i++) {
    sprite_destructor(bots[i]->sp);
    free(bots[i]);
  }
}

void (bot_draw)(bot_t* p){
  if (p->life) sprite_draw(p->sp);
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
    srand(time(0));
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

void (bot_set_dead)(bot_t* bot){
  bot->life = 0;
}

bool (bot_alive)(bot_t* bot){
  return bot->life;
}


// EXPLOSION FUNCTIONS

struct explosion{
  sprite_t* sp;
  int x_map, y_map;
  int r;
  int duration;
  int counter;
};

explosion_t *(explosion_constructor)(){
  explosion_t * ret = malloc(sizeof(explosion_t));
  if (ret == NULL) return NULL;
  sprite_t *sp = sprite_constructor((const char* const*)explosion_xpm);
  ret->sp = sp;
  ret->r = sprite_get_width(sp);
  ret->x_map = 0;
  ret->y_map = 0;
  ret->duration = EXPLOSION_TIME;
  ret->counter = EXPLOSION_TIME;
  return ret;
}

void explosion_destructor(explosion_t *explosion){
  if (explosion == NULL) return;
  sprite_destructor(explosion->sp);
  free(explosion);
}

void (explosion_set_map_pos)(explosion_t *explosion, map_t* map, int xmap, int ymap){
  explosion->x_map = xmap;
  explosion->y_map = ymap;
  int x_px = map_get_Xpixel_pos(map, xmap);
  int y_px = map_get_Ypixel_pos(map, ymap);
  sprite_set_pos(explosion->sp, x_px, y_px);
}

void (explosion_draw)(explosion_t *explosion){
  if (explosion->counter < explosion->duration){
    sprite_draw(explosion->sp);
    explosion->counter++;  
  }
}

void (explosion_expand)(explosion_t *explosion){
  explosion->counter = 0;
}

bool (explosion_ended)(explosion_t *explosion){
  return explosion->counter == explosion->duration;
}


// BOMB FUNCTIONS

struct bomb{
  sprite_t* sp;
  explosion_t** explosions;
  int x_map, y_map;
  int r;
  bool exploded;
  int num_explosion;
  int range;
};

bomb_t* (bomb_constructor)(){
  int num_explosions = (4*BOMB_RANGE)+1;
  bomb_t* bomb = malloc(sizeof(bomb_t));
  explosion_t** explosions = malloc(sizeof(explosion_t*)*num_explosions);
  for (int i=0; i<num_explosions; i++){
    explosions[i] = malloc(sizeof(explosion_t));
    explosion_t * explosion = explosion_constructor();
    sprite_set_pos(explosion->sp, 10, 10);
    explosions[i] = explosion;
  }
  sprite_t* sp = sprite_constructor((const char* const*)bomb_xpm);
  bomb->sp = sp;
  bomb->exploded = true;
  bomb->r = sprite_get_width(sp)/2;
  bomb->explosions = explosions;
  bomb->num_explosion = num_explosions;
  bomb->x_map = 0; bomb->y_map = 0;
  bomb->range = BOMB_RANGE;
  return bomb;
}

void (bomb_destructor)(bomb_t* bomb){
  sprite_destructor(bomb->sp);
  for (int e=0; e < bomb->num_explosion; e++){
    explosion_destructor(bomb->explosions[e]);
  }
  free(bomb);
}

void (bombs_destructor)(bomb_t** bombs){
  for (int i=0; i<NUMBER_OF_BOMBS; i++){
    bomb_destructor(bombs[i]);
  }
}

void (bomb_draw_explosions)(bomb_t* bomb){
  for (int i=0; i<bomb->num_explosion; i++){
    explosion_draw(bomb->explosions[i]);
  }
}

void (bombs_draw)(bomb_t** bombs){
  for(int i=0; i<NUMBER_OF_BOMBS; i++) {
    bomb_t * bomb = bombs[i];
    if(!(bomb->exploded)) sprite_draw(bomb->sp);
      bomb_draw_explosions(bomb);
  }
}

bool (bomb_exploded)(bomb_t* b){
  return b->exploded;
}

int (bomb_get_xmap)(bomb_t* b){
  return b->x_map;
}

int (bomb_get_ymap)(bomb_t* b){
  return b->y_map;
}

void (bomb_explode)(bomb_t* b){
  b->exploded = true;
  for (int i=0; i<b->num_explosion; i++){
    explosion_expand(b->explosions[i]);
  }
}

void bomb_populate(bomb_t** bombs) {
  for(int i=0; i<NUMBER_OF_BOMBS;i++){
    bombs[i] = bomb_constructor();
  }
}

void check_bomb_click(bomb_t** bombs, sprite_t* mouse, int click, int* bombsUsed) {
  if(!click) return;

  int mouse_x = sprite_get_xpos(mouse) + sprite_get_width(mouse) / 2;
  int mouse_y = sprite_get_ypos(mouse) + sprite_get_height(mouse) / 2;

  for(int i=0; i<NUMBER_OF_BOMBS; i++) {
    if(bombs[i]->exploded) continue;

    int bomb_x = sprite_get_xpos(bombs[i]->sp);
    int bomb_y = sprite_get_ypos(bombs[i]->sp);
    int bomb_w = sprite_get_width(bombs[i]->sp);
    int bomb_h = sprite_get_height(bombs[i]->sp);

    if((mouse_x >= bomb_x && mouse_x <= bomb_x + bomb_w) && (mouse_y >= bomb_y && mouse_y <= bomb_y + bomb_h)) {
      bomb_explode(bombs[i]);
      (*bombsUsed)--;
      return;
    }
  }
}

void bomb_set_explosions(bomb_t *bomb, map_t* map){
  int xmap = bomb_get_xmap(bomb);
  int ymap = bomb_get_ymap(bomb);
  int dir = 0; int expl=0;
  while (expl < bomb->num_explosion){
    explosion_t* explosion = bomb->explosions[expl];
    if (expl == 0){
      explosion_set_map_pos(explosion, map, xmap, ymap);
      expl++;
      continue;
    }
    for (int range=1; range <= bomb->range; range++){
      explosion = bomb->explosions[expl];
      switch (dir)
      {
      case 0: // UP EXPLOSION
        explosion_set_map_pos(explosion, map, xmap, ymap-range);
        break; 
      case 1: // DOWN EXPLOSION
        explosion_set_map_pos(explosion, map, xmap, ymap+range);
        break;
      case 2: // RIGHT EXPLOSION
        explosion_set_map_pos(explosion, map, xmap+range, ymap);
        break;
      case 3: // LEFT EXPLOSION
        explosion_set_map_pos(explosion, map, xmap-range, ymap);
        break;
      default:
        break;
      }
      expl++;
    }
    dir++;
  }
}

void (bomb_set_map_pos)(bomb_t *bomb, int xmap, int ymap, int x_px, int y_px){
  sprite_set_speed(bomb->sp,0,0);
  sprite_set_pos(bomb->sp, x_px, y_px);
  bomb->x_map = xmap;
  bomb->y_map = ymap;
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
  sprite_t* wall_sp = sprite_constructor((const char* const*)wall_xpm);
  sprite_t* steel_sp = sprite_constructor((const char* const*)stone_xpm);
  wall->x_map = x;
  wall->y_map = y;
  wall->sp = wall_sp;
  wall->broken = false;
  wall->r = sprite_get_width(wall_sp)/2;
  if ((x==1&&y==1) || (x==2&&y==1) || (x==1&&y==2)) wall->broken = true;
  if (x==0 || y==0 || x==MAP_BLOCKS_SIZE-1 || y==MAP_BLOCKS_SIZE-1 || (x%2 == 0 && y%2 == 0)){
    wall->steel = true;
    sprite_destructor(wall->sp);
    wall->sp = steel_sp;
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
      srand(time(0));
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


void (map_test_player_collisions)(map_t *map, player_t *player){
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

void (map_test_player_bot_collisions)(player_t *player, bot_t** bots){
  for (int i=0; i < NUMBER_OF_BOTS; i++){
    bot_t *bot = bots[i];
    int x0 = player->cx;
    int y0 = player->cy;
    int x = bot->cx;
    int y = bot->cy;
    if (point_distance(x0, y0, x, y) < (bot->r+bot->r) && bot_alive(bot)){
      player->life = 0;
    }
  }
}

void (map_place_bots)(map_t *map, bot_t** bots) {
  int bot_index = 0;
  while(bot_index<NUMBER_OF_BOTS) {

    for(int i=0; i<map->size_map; i++) {
      srand(time(0));
      if(map->walls[i]->broken && (rand() & 1)) {

        if(map->walls[i]->x_map < 3 || map->walls[i]->y_map < 3) continue;

        int x = sprite_get_xpos(map->walls[i]->sp);
        int y = sprite_get_ypos(map->walls[i]->sp);
      
        bots[bot_index] = bot_constructor(x,y);
        bot_index++;
      }
      if(bot_index>=NUMBER_OF_BOTS) break;
    }
  }
}

void (map_place_bomb)(map_t *map, bomb_t *b, int xmap, int ymap) {
  int x_px = map_get_Xpixel_pos(map, xmap);
  int y_px = map_get_Ypixel_pos(map, ymap);
  bomb_set_map_pos(b, xmap, ymap, x_px, y_px);
  bomb_set_explosions(b, map);
  b->exploded = false;
}

int (map_get_Xpixel_pos)(map_t *map, int xmap){
  int wall_sz = sprite_get_width(map->walls[0]->sp);
  int x_px = map->x + (xmap * wall_sz);
  return x_px;
}

int (map_get_Ypixel_pos)(map_t *map, int ymap){
  int wall_sz = sprite_get_height(map->walls[0]->sp);
  int y_px = map->y + (ymap * wall_sz);
  return y_px;
}

void (map_test_explosion_collisions)(map_t *map, player_t *player, bot_t** bots, bomb_t** bombs, int *bombsUsed){
  for (int i=0; i<NUMBER_OF_BOMBS; i++){
    bomb_t* b = bombs[i];
    for (int expl=0; expl < b->num_explosion; expl++){
      explosion_t* explosion = b->explosions[expl];
      if (!explosion_ended(explosion)){
        int xmap = explosion->x_map;
        int ymap = explosion->y_map;
        /** Check player collsion */
        if (player->x_map == xmap && player->y_map == ymap){
          player->life = 0;
        }

        /** Check bots collisions */
        for (int bot=0; bot<NUMBER_OF_BOTS; bot++){
          int bx_map = bot_get_mapx(bots[bot]);
          int by_map = bot_get_mapy(bots[bot]);
          if (bx_map == xmap && by_map == ymap && bot_alive(bots[bot])){
            bot_set_dead(bots[bot]);
          }
        }

        /** Check wall collisions */
        for (int wl=0; wl < map->size_map; wl++){
          wall_t *wall = map->walls[wl];
          int wx_map = wall_get_xmap(wall);
          int wy_map = wall_get_ymap(wall);
          if (wx_map == xmap && wy_map == ymap && !wall_broken(wall)){
            wall_set_broken(wall);
          }
        }

        /** Check bomb collisions */
        for (int bb=0; bb < NUMBER_OF_BOMBS; bb++){
          bomb_t *bomb2 = bombs[bb];
          int bx_map = bomb_get_xmap(bomb2);
          int by_map = bomb_get_ymap(bomb2);
          if (bx_map == xmap && by_map == ymap && !bomb_exploded(bomb2)){
            bomb_explode(bomb2);
            (*bombsUsed)--;
          }
        }
      }
    }
  }
}

// DOOR FUNCTIONS

struct door {
  sprite_t* sp;
  int x_map, y_map;
};

door_t* (door_constructor)(map_t *map){
  door_t *ret = malloc(sizeof(door_t));
  sprite_t *sp = sprite_constructor((const char *const *)door_xpm);
  int xmap = get_odd_random_in_range((map->w_map/2)-1, map->w_map-2);
  int ymap = get_odd_random_in_range((map->h_map/2)-1, map->h_map-2);
  int x_px = map_get_Xpixel_pos(map, xmap);
  int y_px = map_get_Ypixel_pos(map, ymap);
  sprite_set_pos(sp, x_px, y_px);
  sprite_set_speed(sp, 0, 0);
  ret->sp = sp;
  ret->x_map = xmap;
  ret->y_map = ymap;
  wall_t *wall = map->walls[xmap+ymap*map->w_map];
  wall->broken = false;
  return ret;
}

void (door_destructor)(door_t *door){
  sprite_destructor(door->sp);
  free(door);
}

void (door_draw)(door_t *door){
  sprite_draw(door->sp);
}

int (door_get_xmap_pos)(door_t *door){
  return door->x_map;
}

int (door_get_ymap_pos)(door_t *door){
  return door->y_map;
}

