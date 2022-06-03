#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "rectangle.h"
#include "sprite.h"
typedef struct menu menu_t;


/**
 * @brief Construct menu.
 * @param   fnt Font to use when rendering menu options text
 * @return      Pointer to constructed menu, or NULL if failed.
 */
menu_t* (menu_ctor)();
/**
 * @brief Destruct menu.
 * @param   p   Pointer to menu to destruct
 */
void (menu_dtor)(menu_t *menu);
/**
 * @brief Update menu state.
 *
 * This function allows to check if the mouse is hovering over an item, and knowing
 * if an item was clicked.
 * @param   menu    Pointer to menu
 * @param   click   0 if mouse right button is clicked, other value otherwise
 * @return  selected option if clicked, -1 otherwise
 */
int (menu_update_state)(menu_t *menu, sprite_t *sp, int click);
/**
 * @brief Draw menu on screen buffer.
 * @param   menu    Pointer to menu to be drawn
 */
void (menu_draw)(menu_t *menu);

/**
 * @}
 */

#endif //MENU_H_INCLUDED
