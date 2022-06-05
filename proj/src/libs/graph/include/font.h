#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include "sprite.h"
#include "char65.xpm"
#include "char66.xpm"

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

void (font_draw_string)(font_t *font, char* string, size_t sz, uint16_t x, uint16_t y);

/**
 * @}
 */

#endif //MENU_H_INCLUDED
