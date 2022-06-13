#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include "sprite.h"
#include "font_macros.h"
#include "keyboard_macros.h"
#include "char44.xpm"
#include "char46.xpm"
#include "char47.xpm"
#include "char48.xpm"
#include "char49.xpm"
#include "char50.xpm"
#include "char51.xpm"
#include "char52.xpm"
#include "char53.xpm"
#include "char54.xpm"
#include "char55.xpm"
#include "char56.xpm"
#include "char57.xpm"
#include "char58.xpm"
#include "char65.xpm"
#include "char66.xpm"
#include "char67.xpm"
#include "char68.xpm"
#include "char69.xpm"
#include "char70.xpm"
#include "char71.xpm"
#include "char72.xpm"
#include "char73.xpm"
#include "char74.xpm"
#include "char75.xpm"
#include "char76.xpm"
#include "char77.xpm"
#include "char78.xpm"
#include "char79.xpm"
#include "char80.xpm"
#include "char81.xpm"
#include "char82.xpm"
#include "char83.xpm"
#include "char84.xpm"
#include "char85.xpm"
#include "char86.xpm"
#include "char87.xpm"
#include "char88.xpm"
#include "char89.xpm"
#include "char90.xpm"

/**
 * @defgroup font font
 * @ingroup graph
 * @{
 */

/**
 * Font struct definition
 */
typedef struct font font_t;

/**
 * Font constructor
 * @return font struct pointer
 */
font_t* (font_ctor)();
/**
 * Font destructor
 * @param font font struct pointer
 */
void (font_dtor)(font_t *font);
/**
 * Load each xpm img of each character to the array of sprites in the font struct
 * @param font font struct pointer
 */
void (font_load_glyphs)(font_t *font);
/**
 * Draw a c string to the screen
 * @param font font struct pointer
 * @param phrase c string to be drawn
 * @param x x position in pixels
 * @param y y position in pixels
 */
void (font_draw_string)(font_t *font, char* phrase, uint16_t x, uint16_t y);
/**
 * Get width of each character in the font
 * @param font font struct pointer
 * @return width of a character
 */
int (font_get_char_width)(font_t *font);
/**
 * Get height of each character in the font
 * @param font font struct pointer
 * @return height of a character
 */
int (font_get_char_height)(font_t *font);


/**
 * @}
 */

#endif //MENU_H_INCLUDED
