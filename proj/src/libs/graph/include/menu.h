#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "rectangle.h"
#include "sprite.h"
#include "font.h"
/**
 * @defgroup menu menu
 * @ingroup graph
 * @{
 */

/**
 * Menu struct definition
 */
typedef struct menu menu_t;

/**
 * Menu constructor
 * @param font font struct pointer
 * @param n_buttons number of buttons in the menu
 * @return menu struct pointer
 */
menu_t* (menu_ctor)(font_t *font, size_t n_buttons);
/**
 * Construct new button in the menu
 * @param menu menu struct pointer
 * @param x x position in pixels
 * @param y y position in pixels
 * @param w width of the button
 * @param h height of the button
 * @param phrase c string to display in the button
 */
void menu_add_button(menu_t * menu, int16_t x, int16_t y, uint16_t w, uint16_t h, char* phrase);
/**
 * Menu destructor
 * @param p Menu struct pointer
 */
void (menu_dtor)(menu_t *menu);
/**
 * Update menu state, allowing it to check if the mouse is hovering over an button, and knowing if user clicked on it
 * @param menu menu struct pointer
 * @param click 0 if mouse right button is clicked or other value otherwise
 * @return selected option if clicked or -1 otherwise
 */
int (menu_update_state)(menu_t *menu, sprite_t *sp, int click);
/**
 * Draw menu on screen
 * @param menu Menu struct pointer
 */
void (menu_draw)(menu_t *menu);

/**
 * @}
 */

#endif //MENU_H_INCLUDED
