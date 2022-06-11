#ifndef ENTITIES_H_INCLUDED
#define ENTITIES_H_INCLUDED

#include "project_functions.h"
#include "keys.h"

typedef enum{
  EMPTY,
  PLAYER,
  ENEMY,
  WALL, 
  EXPLOSION
}element_t;


typedef struct player player_t;
typedef struct bot bot_t;
typedef struct explosion explosion_t;
typedef struct bomb bomb_t;
typedef struct wall wall_t;
typedef struct map map_t;


// PLAYER FUNCTIONS

player_t* (player_constructor)(int x, int y);
void (player_destructor)(player_t* p);
void (player_draw)(player_t* p);
int (player_get_x)(player_t* p);
int (player_get_y)(player_t* p);
void (player_set_pos)(player_t* p, int x, int y);
int (player_get_mapx)(player_t* p);
int (player_get_mapy)(player_t* p);
void (player_set_map_pos)(player_t* p, int x, int y);
void (player_set_center)(player_t* p, int cx, int cy);
int (player_process_key)(uint8_t bbyte[2], int size, keys_t *keys);
void (player_set_speed)(player_t *player, keys_t *keys);

void (player_check_place_bomb)(map_t* map, player_t *player, keys_t *keys, bomb_t **bombs, int *bombsUsed);



// BOT FUNCTIONS

bot_t* (bot_constructor)(int x, int y);
void (bot_destructor)(bot_t** bots);
void (bot_draw)(bot_t* p);
int (bot_get_x)(bot_t* p);
int (bot_get_y)(bot_t* p);
void (bot_set_pos)(bot_t* p, int x, int y);
int (bot_get_mapx)(bot_t* p);
int (bot_get_mapy)(bot_t* p);
void (bot_set_map_pos)(bot_t* p, int x, int y);
void (bot_set_center)(bot_t* p, int cx, int cy);
void (bot_move)(bot_t* bot);


// EXPLOSION FUNCTIONS

explosion_t* (explosion_constructor)();
void (explosion_destructor)(explosion_t* bombs);
void (explosion_set_map_pos)(explosion_t *explosion, map_t* map, int xmap, int ymap);
void (explosion_draw)(explosion_t *explosion);
bool (explosion_ended)(explosion_t *explosion);
void (explosion_expand)(explosion_t *explosion);


// BOMB FUNCTIONS


bomb_t* (bomb_constructor)();
void (bombs_destructor)(bomb_t** bombs);
void (bomb_destructor)(bomb_t* bomb);
void (bombs_draw)(bomb_t** bombs);
void (bomb_draw_explosions)(bomb_t* bomb);
bool (bomb_exploded)(bomb_t* b);
int (bomb_get_xmap)(bomb_t* b);
int (bomb_get_ymap)(bomb_t* b);
void (bomb_explode)(bomb_t* b);
void (bomb_populate)(bomb_t** bombs);
void (check_bomb_click)(bomb_t** bombs, sprite_t* mouse, int click, int* bombsUsed);
void (bomb_set_explosions)(bomb_t *bomb, map_t* map);
void (bomb_set_map_pos)(bomb_t *bomb, int xmap, int ymap, int x_px, int y_px);

// WALL FUNCTIONS

wall_t* (wall_constructor)(int x, int y);
void (wall_destructor)(wall_t* wall);
void (wall_draw)(wall_t* w);
bool (wall_broken)(wall_t* w);
int (wall_get_xmap)(wall_t* w);
int (wall_get_ymap)(wall_t* w);
void (wall_set_broken)(wall_t* w);


// MAP FUNCTIONS

map_t* (map_constructor)();
void (map_destructor)(map_t *map);
void (map_draw)(map_t *map);
void (map_update_player_grid)(map_t *map, player_t *player);
void (map_update_bot_grid)(map_t *map, bot_t *bot);
void (map_test_collisions)(map_t *map, player_t *player);
void (map_test_bot_collisions)(map_t *map, bot_t *bot);
void (map_place_bots)(map_t *map, bot_t** bots);
void (map_place_bomb)(map_t *map, bomb_t* bomb, int xmap, int ymap);
int (map_get_Xpixel_pos)(map_t *map, int xmap);
int (map_get_Ypixel_pos)(map_t *map, int ymap);

#endif
