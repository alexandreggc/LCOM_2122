#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED

#include "font.h"

/**
 * @defgroup rectangle rectangle
 * @ingroup graph
 */
/**
 * Rectangle struct definition
 */
typedef struct rectangle rectangle_t;
struct rectangle{
    uint16_t  x, y, w, h;
    uint32_t color;
    font_t *font;
    char *phrase;
};


/**
 * Rectangle contructor
 * @param x x position of upper-left corner
 * @param y y position of upper-left corner
 * @param w width
 * @param h height
 * @param font font struct pointer
 * @param phrase c string to be written inside the rectangle
 * @return rectangle struct pointer
 */
rectangle_t* (rectangle_ctor)(int16_t x, int16_t y, uint16_t w, uint16_t h, font_t *font, char* phrase);
/**
* Rectangle destructor
* @param rectangle rectangle struct pointer
*/
void(rectangle_dtor)(rectangle_t *rectangle);
/**
* Set rectangle position
* @param p rectangle struct pointer
* @param x x position of the upper-left corner
* @param y y position of the upper-left corner
*/
void(rectangle_set_pos)(rectangle_t *p,  int16_t x,  int16_t y);
/**
 * Set rectangle size
 * @param p rectangle struct pointer
 * @param w width
 * @param h height
 */
void(rectangle_set_size)(rectangle_t *p, uint16_t w, uint16_t h);
/**
 * Set rectangle fill color
 * @param p pointer to rectangle
 * @param color color to fill rectangle
 */
void(rectangle_set_fill_color)(rectangle_t *p, uint32_t color);
/**
 * Get rectangle x position
 * @param p pointer to rectangle
 * @return rectangle x position
 */
int16_t  (rectangle_get_x)(const rectangle_t *p);
/**
 * Get rectangle y position
 * @param p pointer to rectangle
 * @return rectangle y position
 */
int16_t  (rectangle_get_y)(const rectangle_t *p);
/**
 * Get rectangle width.
 * @param p rectangle struct pointer
 * @return rectangle width
 */
uint16_t (rectangle_get_w)(const rectangle_t *p);
/**
 * Get rectangle height
 * @param p rectangle struct pointer
 * @return rectangle height
 */
uint16_t (rectangle_get_h)(const rectangle_t *p);
/**
 * Check if point in screen coordinates is inside the rectangle
 * @param p pointer to rectangle
 * @param x x position of the point
 * @param y y position of the point
 * @return true if the point is inside the rectangle, false otherwise
 */
int (rectangle_collide_point)(const rectangle_t *p, int x, int y);
/**
 * Draw rectangle in screen buffer
 * @param p pointer to rectangle to be drawn
 */
void (rectangle_draw)(rectangle_t *p);
/**
 * Get the start x position to draw the string of the rectangle
 * @param p rectangle struct pointer
 * @return start x position
 */
int (rectangle_draw_start_x)(rectangle_t *p);
/**
 * Get the start y position to draw the string of the rectangle
 * @param p rectangle struct pointer
 * @return start y position
 */
int (rectangle_draw_start_y)(rectangle_t *p);


/**
 * @}
 */

#endif //RECTANGLE_H_INCLUDED
