#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include "project_macros.h"
/**
 * @defgroup sprite sprite
 * @ingroup graph
 * @{
 */

/**
 * Sprite struct definition
 */
typedef struct sprite sprite_t;
/**
 * Sprite contructor
 * @param xpm pixmap xpm image
 * @return sprite struct pointer
 */
sprite_t* (sprite_constructor)(const char *const *xpm);
/**
 * Sprite destructor
 * @param sp sprite struct pointer
 */
void (sprite_destructor)(sprite_t *sp);
/**
 * Get width of the sprite image
 * @param sp sprite struct pointer
 * @return width of the sprite
 */
int (sprite_get_width)(sprite_t *sp);
/**
 * Get the height of the sprite image
 * @param sp sprite struct pointer
 * @return height of the sprite
 */
int (sprite_get_height)(sprite_t *sp);
/**
 * Get x position in pixels of the sprite
 * @param sp sprite struct pointer
 * @return x position in pixels
 */
int (sprite_get_xpos)(sprite_t *sp);
/**
 * Get y position in pixels of the sprite
 * @param sp sprite struct pointer
 * @return y position of the sprite
 */
int (sprite_get_ypos)(sprite_t *sp);
/**
 * Get x speed of the sprite
 * @param sp sprite struct pointer
 * @return x speed of the sprite
 */
int (sprite_get_xspeed)(sprite_t *sp);
/**
 * Get y speed of sprite
 * @param sp sprite struct pointer
 * @return y speed of sprite
 */
int (sprite_get_yspeed)(sprite_t *sp);
/**
 * Set positions to the given sprite
 * @param sp sprite struct pointer
 * @param x x position of the sprite
 * @param y y position of the sprite
 */
void (sprite_set_pos)(sprite_t *sp, int x, int y);
/**
 * Update sprite position with adding his speed
 * @param sp sprite struct pointer
 */
void (sprite_update_pos)(sprite_t *sp);
/**
 * Set sprite x and y speed
 * @param sp sprite struct pointer
 * @param vx x speed of the sprite
 * @param vy y speed of the sprite
 */
void(sprite_set_speed)(sprite_t *sp, int vx, int vy);
/**
 * Draw sprite on screen
 * @param sp sprite struct pointer
 */
void (sprite_draw)(sprite_t *sp);
/**
 * @}
 */
#endif
