#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED

#include "font.h"

typedef struct rectangle rectangle_t;
struct rectangle{
    uint16_t  x, y, w, h;
    uint32_t color;
    font_t *font;
    char *phrase;
};

/**
 * @brief Construct rectangle.
 * @param   x   X-position of upper-left corner
 * @param   y   Y-position of upper-left corner
 * @param   w   Width
 * @param   h   Height
 * @return      Pointer to constructed rectangle, or NULL if failed
 */
rectangle_t* (rectangle_ctor)(int16_t x, int16_t y, uint16_t w, uint16_t h, font_t *font, char* phrase);
/**
 * @brief Destruct rectangle.
 * @param   p   Pointer to rectangle to be destructed
 */
void         (rectangle_dtor)(rectangle_t *rectangle);
/**
 * @brief Set rectangle position.
 * @param   p   Pointer to rectangle
 * @param   x   X-position of the upper-left corner
 * @param   y   Y-position of the upper-left corner
 */
void (rectangle_set_pos)          (rectangle_t *p,  int16_t x,  int16_t y);
/**
 * @brief Set rectangle size.
 * @param   p   Pointer to rectangle
 * @param   w   Width
 * @param   h   Height
 */
void (rectangle_set_size)         (rectangle_t *p, uint16_t w, uint16_t h);
/**
 * @brief Set rectangle fill color.
 * @param   p       Pointer to rectangle
 * @param   color   Color to fill rectangle
 */
void (rectangle_set_fill_color)   (rectangle_t *p, uint32_t color);
/**
 * @brief Get rectangle x-position.
 * @param   p   Pointer to rectangle
 * @return      Rectangle x-position
 */
int16_t  (rectangle_get_x)(const rectangle_t *p);
/**
 * @brief Get rectangle y-position.
 * @param   p   Pointer to rectangle
 * @return      Rectangle y-position
 */
int16_t  (rectangle_get_y)(const rectangle_t *p);
/**
 * @brief Get rectangle width.
 * @param   p   Pointer to rectangle
 * @return      Rectangle width
 */
uint16_t (rectangle_get_w)(const rectangle_t *p);
/**
 * @brief Get rectangle height.
 * @param   p   Pointer to rectangle
 * @return      Rectangle height
 */
uint16_t (rectangle_get_h)(const rectangle_t *p);
/**
 * @brief Know if point in screen coordinates lies inside rectangle.
 * @param   p   Pointer to rectangle
 * @param   x   X-position of the point
 * @param   y   Y-position of the point
 * @return      True if the point lies inside the rectangle, false otherwise.
 */
int      (rectangle_collide_point)(const rectangle_t *p, int x, int y);
/**
 * Draw rectangle in screen buffer.
 * @param   p   Pointer to rectangle to be drawn
 */
void (rectangle_draw)(rectangle_t *p);

int (rectangle_draw_start_x)(rectangle_t *p);

int (rectangle_draw_start_y)(rectangle_t *p);


/**
 * @}
 */

#endif //RECTANGLE_H_INCLUDED
