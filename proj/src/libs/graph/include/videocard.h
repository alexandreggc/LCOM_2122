#ifndef VIDEOCARD_H_INCLUDED
#define VIDEOCARD_H_INCLUDED

#include "graphics_card_macros.h"
/**
 * @defgroup graph graph
 * @ingroup libs
 */

/**
 * @defgroup videocard videocard
 * @ingroup graph
 *
 * @{
 */
/**
 * Set the graphics card to given mode
 * @param mode new graphics mode value
 * @return 0 if success or 1 otherwise
 */
int (set_graphics_mode)(uint16_t mode);
/**
 * Map and allocate video memory
 * @param mode graphics card mode
 * @return 0 if success or 1 otherwise
 */
int (map_vram)(uint16_t mode);
/**
 * Draw horizontal line to screen
 * @param x x position in pixels
 * @param y y position in pixel
 * @param width width of the line
 * @param color color od the line
 * @return 0 if success or 1 otherwise
 */
int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t width, uint32_t color);
/**
 * Draw rectangle to screen
 * @param x x position in pixels
 * @param y y position in pixels
 * @param width width of the rectangle
 * @param height height of the rectangule
 * @param color color of the rectangle
 * @return 0 if success or 1 otherwise
 */
int(vg_draw_rectangle)(uint16_t x, uint16_t y,uint16_t width, uint16_t height,uint32_t color);
/**
 * Draw pixel to screen, copying its color to the video buffer
 * @param x x position in pixels
 * @param y y position in pixels
 * @param color color of the pixel
 * @return 0 if success or 1 otherwise
 */
int(vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);
/**
 * Draw xpm image in given position
 * @param xpm_img xpm image struct pointer
 * @param x x position in pixels
 * @param y y position in pixels
 * @return 0 if success or 1 otherwise
 */
int(vg_draw_xpm_img)(xpm_image_t *xpm_img, uint16_t x, uint16_t y);
/**
 * Clear screen by resetting the video buffer to 0
 * @return 0 if success or 1 otherwise
 */
int(vg_clear_screen)();
/**
 * Copy the video buffer to the actual video memory
 * @return 0 if success or 1 otherwise
 */
int (vg_draw)();
/**
 * Get width of a rectangle given the number os rectangles to display on screen
 * @param no_rectangles number of rectangles
 * @return 0 if success or 1 otherwise
 */
uint8_t (get_rectangles_width)(uint8_t no_rectangles);
/**
 * Get height of a rectangle given the number os rectangles to display on screen
 * @param no_rectangles number of rectangles
 * @return 0 if success or 1 otherwise
 */
uint8_t (get_rectangles_height)(uint8_t no_rectangles);
/**
 * Get vertical resolution
 * @return vertical resolution
 */
uint16_t (get_graph_y_res)();
/**
 * Get horizontal resolution
 * @return horizontal resolution
 */
uint16_t (get_graph_x_res)();
/**
 * @}
 */
#endif
