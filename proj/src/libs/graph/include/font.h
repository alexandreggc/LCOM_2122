#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include "sprite.h"
#include "font_macros.h"
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

typedef struct font font_t;


/**
 * @brief Construct menu.
 * @param   fnt Font to use when rendering menu options text
 * @return      Pointer to constructed menu, or NULL if failed.
 */
font_t* (font_ctor)(size_t sz);
/**
 * @brief Destruct menu.
 * @param   p   Pointer to menu to destruct
 */
void (font_dtor)(font_t *font);
/**
 * @brief Update menu state.
 *
 * This function allows to check if the mouse is hovering over an item, and knowing
 * if an item was clicked.
 * @param   menu    Pointer to menu
 * @param   click   0 if mouse right button is clicked, other value otherwise
 * @return  selected option if clicked, -1 otherwise
 */
/**
 * @brief Draw menu on screen buffer.
 * @param   menu    Pointer to menu to be drawn
 */
void (font_load_glyphs)(font_t *font);

void (font_draw_string)(font_t *font, char* phrase, uint16_t x, uint16_t y);

int (font_get_char_width)(font_t *font);

int (font_get_char_height)(font_t *font);


/**
 * @}
 */

#endif //MENU_H_INCLUDED
