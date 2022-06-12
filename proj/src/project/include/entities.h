#ifndef ENTITIES_H_INCLUDED
#define ENTITIES_H_INCLUDED

#include "project_functions.h"
#include "keys.h"

typedef enum{
  EMPTY,
  PLAYER,
  BOT
}element_t;

/**
 * Door struct
 */
typedef struct door door_t;
/**
 * Player struct
 */
typedef struct player player_t;
/**
 * Bot struct
 */
typedef struct bot bot_t;
/**
 * Explosion struct
 */
typedef struct explosion explosion_t;
/**
 * Bomb struct
 */
typedef struct bomb bomb_t;
/**
 * Wall struct
 */
typedef struct wall wall_t;
/**
 * Map struct
 */
typedef struct map map_t;


// PLAYER FUNCTIONS
/**
 * Player constructor
 * @param x x position in pixels on screen
 * @param y y position in pixels on screen
 * @return player struct pointer
 */
player_t* (player_constructor)(int x, int y);
/**
 * Player destructor
 * @param p player struct pointer to be destructed
 */
void (player_destructor)(player_t* p);
/**
 * Draw player on screen
 * @param p player struct pointer to be drawn
 */
void (player_draw)(player_t* p);
/**
 * Get x position in pixels of the player argument
 * @param p player struct pointer
 * @return x position in pixels
 */
int (player_get_x)(player_t* p);
/**
 * Get y position in pixels of the player argument
 * @param p player struct pointer
 * @return y position in pixels
 */
int (player_get_y)(player_t* p);
/**
 * Set player position in pixels, matching the arguments
 * @param p player struct pointer
 * @param x x position in pixels
 * @param y y position in pixels
 */
void (player_set_pos)(player_t* p, int x, int y);
/**
 * Get player x position in the map matrix
 * @param p player struct pointer
 * @return x position in the map matrix
 */
int (player_get_mapx)(player_t* p);
/**
 * Get player y position in the map matrix
 * @param p player struct pointer
 * @return y position in the map matrix
 */
int (player_get_mapy)(player_t* p);
/**
 * Set player position int the map matrix, matching the arguments
 * @param p player struct pointer
 * @param x x position in map matrix
 * @param y y position in map matrix
 */
void (player_set_map_pos)(player_t* p, int x, int y);
/**
 * Set player center positions in pixels, matching the arguments
 * @param p player struct pointer
 * @param cx x center position in pixels
 * @param cy y center position in pixels
 */
void (player_set_center)(player_t* p, int cx, int cy);

int (player_process_key)(uint8_t bbyte[2], int size, keys_t *keys);
/**
 *Set player speed matching the keys that are being pressed
 * @param player player struct pointer
 * @param keys current keys state, keys struct pointer
 */
void (player_set_speed)(player_t *player, keys_t *keys);
/**
 * Places a bomb checking first if player can place a bomb in his position and updated the number of used bombs
 * @param map map struct pointer
 * @param player player struct pointer
 * @param keys keys struct pointer
 * @param bombs array of bomb struct pointers
 * @param bombsUsed number of bombs used, int variable pointer
 */
void (player_check_place_bomb)(map_t* map, player_t *player, keys_t *keys, bomb_t **bombs, int *bombsUsed);
/**
 * Check if player is alive and return his state
 * @param player player struct pointer
 * @return true if player is alive or false otherwise
 */
bool (player_alive)(player_t *player);
/**
 * Set player to be alive
 * @param player player struct pointer
 */
void (player_set_alive)(player_t *player);
/**
 * Check if player is exiting through the door passed in the argument
 * @param player player struct pointer
 * @param door door struct pointer
 * @return true if player went through the door or false otherwise
 */
bool (player_test_exit_door)(player_t *player, door_t *door);


// BOT FUNCTIONS
/**
 * Bot constructor
 * @param x x position in pixels on screen
 * @param y y position in pixels on screen
 * @return bot struct pointer
 */
bot_t* (bot_constructor)(int x, int y);
/**
 * Bots destructor
 * @param bots array of bot struct pointer to be destructed
 */
void (bot_destructor)(bot_t** bots);
/**
 * Draw bot passed in the argument
 * @param p bot struct pointer
 */
void (bot_draw)(bot_t* p);
/**
 * Get bot x position in pixels on screen
 * @param p bot struct pointer
 * @return x position in pixels
 */
int (bot_get_x)(bot_t* p);
/**
 * Get bot y position in pixels on screen
 * @param p bot struct pointer
 * @return y position in pixels
 */
int (bot_get_y)(bot_t* p);
/**
 * Set bot position matching the arguments
 * @param p bot struct pointer
 * @param x x position in pixels on the screen
 * @param y y position in pixels on the screen
 */
void (bot_set_pos)(bot_t* p, int x, int y);
/**
 * Get bot x position in map matrix
 * @param p bot struct pointer
 * @return x position in the map matrix
 */
int (bot_get_mapx)(bot_t* p);
/**
 * Get bot y position in map matrix
 * @param p bot struct pointer
 * @return y position in map matrix
 */
int (bot_get_mapy)(bot_t* p);
/**
 * Set bot position in map matrix
 * @param p bot struct pointer
 * @param x x position in map matrix
 * @param y y position in map matrix
 */
void (bot_set_map_pos)(bot_t* p, int x, int y);
/**
 * Set bot center position in pixels on screen
 * @param p bot struct pointer
 * @param cx x center position in pixels
 * @param cy y center position in pixels
 */
void (bot_set_center)(bot_t* p, int cx, int cy);
/**
 * Move bot in a random direction
 * @param bot bot struct pointer
 */
void (bot_move)(bot_t* bot);
/**
 * Set bot to dead state
 * @param bot bot struct pointer
 */
void (bot_set_dead)(bot_t* bot);
/**
 * Check if bot is alive
 * @param bot bot struct pointer
 * @return true if bot is alive or false otherwise
 */
bool (bot_alive)(bot_t* bot);


// EXPLOSION FUNCTIONS
/**
 * Explosion constructor
 * @return explosion struct pointer
 */
explosion_t* (explosion_constructor)();
/**
 * Explosion destructor
 * @param bombs explosion struct pointers
 */
void (explosion_destructor)(explosion_t* bombs);
/**
 * Set explosion position on map matching the position arguments
 * @param explosion explosion struct pointer
 * @param map map struct pointer
 * @param xmap x position in map matrix
 * @param ymap y position in map matrix
 */
void (explosion_set_map_pos)(explosion_t *explosion, map_t* map, int xmap, int ymap);
/**
 * Draw explosion checking if it is active
 * @param explosion explosion struct pointer
 */
void (explosion_draw)(explosion_t *explosion);
/**
 * Checks if explosion has ended
 * @param explosion explosion struct pointer
 * @return true if it has ended or false otherwise
 */
bool (explosion_ended)(explosion_t *explosion);
/**
 * Expands the argument's explosion resetting its counter, explosion is now active
 * @param explosion explosion struct pointer
 */
void (explosion_expand)(explosion_t *explosion);


// BOMB FUNCTIONS

/**
 * Bomb constructor
 * @return bomb struct pointer
 */
bomb_t* (bomb_constructor)();
/**
 * Bombs destructor
 * @param bombs array of bomb struct pointers
 */
void (bombs_destructor)(bomb_t** bombs);
/**
 * Bomb destructor
 * @param bomb bomb struct pointer
 */
void (bomb_destructor)(bomb_t* bomb);
/**
 * Draw bombs passed in the argument
 * @param bombs array of bomb struct pointers
 */
void (bombs_draw)(bomb_t** bombs);
/**
 * Draw bomb explosions if they are active
 * @param bomb bomb struct pointer
 */
void (bomb_draw_explosions)(bomb_t* bomb);
/**
 * Checks if bomb has exploded
 * @param b bomb struct pointer
 * @return true if it has exploded or false otherwise
 */
bool (bomb_exploded)(bomb_t* b);
/**
 * Get bomb x position in map matrix
 * @param b bomb struct pointer
 * @return x position in map matrix
 */
int (bomb_get_xmap)(bomb_t* b);
/**
 * Get bomb y position in map matrix
 * @param b bomb struct pointer
 * @return y position in map matrix
 */
int (bomb_get_ymap)(bomb_t* b);
/**
 * Set bomb to exploded
 * @param b bomb struct pointer
 */
void (bomb_explode)(bomb_t* b);
/**
 * Construct the array of bombs passed in the argument
 * @param bombs array of bomb struct pointer
 */
void (bomb_populate)(bomb_t** bombs);
/**
 * Checks for each bomb in the array if it was clicked and making it explode
 * @param bombs array of bomb struct pointer
 * @param mouse mouse struct pointer
 * @param click true if there was a click or false otherwise
 */
void (check_bomb_click)(bomb_t** bombs, sprite_t* mouse, int click);
/**
 * Set and construct the bomb explosions for the bomb in the argument
 * @param bomb bomb struct pointer
 * @param map map struct pointer
 */
void (bomb_set_explosions)(bomb_t *bomb, map_t* map);
/**
 * Set bomb position in the map matrix and in pixels matching the arguments
 * @param bomb bomb struct pointer
 * @param xmap bomb x position in the map matrix
 * @param ymap bomb y position in the map matrix
 * @param x_px bomb x position in pixels on screen
 * @param y_px bomb y position in pixels on screen
 */
void (bomb_set_map_pos)(bomb_t *bomb, int xmap, int ymap, int x_px, int y_px);

// WALL FUNCTIONS
/**
 * Wall constructor
 * @param x wall x position in pixels on screen
 * @param y wall y position in pixels on screen
 * @return wall struct pointer
 */
wall_t* (wall_constructor)(int x, int y);
/**
 * Wall destructor
 * @param wall wall struct pointer
 */
void (wall_destructor)(wall_t* wall);
/**
 * Draw wall on screen if it's not broken
 * @param w wall struct pointer
 */
void (wall_draw)(wall_t* w);
/**
 * Check if wall is broken
 * @param w wall struct pointer
 * @return true of it is broken or false otherwise
 */
bool (wall_broken)(wall_t* w);
/**
 * Get wall x position in map matrix
 * @param w wall struct pointer
 * @return wall x position in map matrix
 */
int (wall_get_xmap)(wall_t* w);
/**
 * Get wall y position in map matrix
 * @param w wall struct pointer
 * @return wall y position in map matrix
 */
int (wall_get_ymap)(wall_t* w);
/**
 * Set wall to broken state
 * @param w wall struct pointer
 */
void (wall_set_broken)(wall_t* w);


// DOOR FUNCTIONS
/**
 * Door constructor, setting door to random position on bottom left part of screen
 * @param map map struct pointer
 * @return door struct pointer
 */
door_t* (door_constructor)(map_t *map);
/**
 * Door destructor
 * @param door door struct pointer
 */
void (door_destructor)(door_t *door);
/**
 * Draw door on screen
 * @param door door struct pointer
 */
void (door_draw)(door_t *door);
/**
 * Get door x position in map matrix
 * @param door door struct pointer
 * @return door x position in map matrix
 */
int (door_get_xmap_pos)(door_t *door);
/**
 * Get door y position in map matrix
 * @param door door struct pointer
 * @return door y position in map matrix
 */
int (door_get_ymap_pos)(door_t *door);


// MAP FUNCTIONS
/**
 * Map constructor, with random position of breakable walls
 * @return map struct pointer
 */
map_t* (map_constructor)();
/**
 * Map destructor
 * @param map map struct pointer
 */
void (map_destructor)(map_t *map);
/**
 * Draw map on screen
 * @param map map struct pointer
 */
void (map_draw)(map_t *map);
/**
 * Updated the player position on the map matrix
 * @param map map struct pointer
 * @param player player struct pointer
 */
void (map_update_player_grid)(map_t *map, player_t *player);
/**
 * Updated the bot position on the map matrix
 * @param map map struct pointer
 * @param bot bot struct pointer
 */
void (map_update_bot_grid)(map_t *map, bot_t *bot);
/**
 * Manage collisions between the player and the map
 * @param map map struct pointer
 * @param player player struct pointer
 */
void (map_test_player_collisions)(map_t *map, player_t *player);
/**
 * Manage collision between the player and the bots
 * @param player player struct pointer
 * @param bots array of bots struct pointers
 */
void (map_test_player_bot_collisions)(player_t *player, bot_t** bots);
/**
 * Manage collision between the map and the bots
 * @param map map struct pointer
 * @param bot bot struct pointer
 */
void (map_test_bot_collisions)(map_t *map, bot_t *bot);
/**
 * Manage collisions between the bomb explosions and the map walls, player and bots
 * @param map map struct pointer
 * @param player player struct pointer
 * @param bots array of bots struct pointers
 * @param bombs array of bombs struct pointers
 * @param bombsUsed number of used bombs passed by reference
 */
void (map_test_explosion_collisions)(map_t *map, player_t *player, bot_t** bots, bomb_t** bombs, int *bombsUsed);
/**
 * Fill the array of bots, placing them on correct map positions
 * @param map map struct pointer
 * @param bots array of bots struct pointers
 */
void (map_place_bots)(map_t *map, bot_t** bots);
/**
 * Place a bomb on the screen, matching the position arguments
 * @param map map struct pointer
 * @param bomb bomb struct pointer
 * @param xmap bomb x position in map matrix
 * @param ymap bomb y position in map matrix
 */
void (map_place_bomb)(map_t *map, bomb_t* bomb, int xmap, int ymap);
/**
 * Get x position on screen given an x position in the map matrix
 * @param map map struct pointer
 * @param xmap x position in map matrix
 * @return x position in pixels on screen
 */
int (map_get_Xpixel_pos)(map_t *map, int xmap);
/**
 * Get y position on screen given an y position in the map matrix
 * @param map map struct pointer
 * @param ymap y position in map matrix
 * @return y position in pixels on screen
 */
int (map_get_Ypixel_pos)(map_t *map, int ymap);


#endif
