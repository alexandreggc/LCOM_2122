#ifndef ENTITIES_H_INCLUDED
#define ENTITIES_H_INCLUDED

typedef enum{
  EMPTY,
  PLAYER,
  ENEMY,
  WALL
}element_t;

// PLAYER FUNCTIONS

typedef struct player player_t;

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
int (player_process_key)(uint8_t bbyte[2], int size, player_t* player);


// BOT FUNCTIONS

typedef struct bot bot_t;

bot_t* (bot_constructor)(int x, int y);
void (bot_destructor)(bot_t* p);
void (bot_draw)(bot_t* p);
int (bot_get_x)(bot_t* p);
int (bot_get_y)(bot_t* p);
void (bot_set_pos)(bot_t* p, int x, int y);
int (bot_get_mapx)(bot_t* p);
int (bot_get_mapy)(bot_t* p);
void (bot_set_map_pos)(bot_t* p, int x, int y);
void (bot_set_center)(bot_t* p, int cx, int cy);
void (bot_move)(bot_t* bot);


// WALL FUNCTIONS

typedef struct wall wall_t;

wall_t* (wall_constructor)(int x, int y);
void (wall_destructor)(wall_t* wall);
void (wall_draw)(wall_t* w);
bool (wall_broken)(wall_t* w);
int (wall_get_xmap)(wall_t* w);
int (wall_get_ymap)(wall_t* w);
void (wall_set_broken)(wall_t* w);


// MAP FUNCTIONS

typedef struct map map_t;

map_t* (map_constructor)();
void (map_destructor)(map_t *map);
void (map_draw)(map_t *map);
void (map_update_player_grid)(map_t *map, player_t *player);
void (map_update_bot_grid)(map_t *map, bot_t *bot);
void (map_test_collisions)(map_t *map, player_t *player);
void (map_test_bot_collisions)(map_t *map, bot_t *bot);

#endif
