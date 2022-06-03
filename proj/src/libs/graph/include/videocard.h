#ifndef VIDEOCARD_H_INCLUDED
#define VIDEOCARD_H_INCLUDED

#include "graphics_card_macros.h"

int (set_graphics_mode)(uint16_t mode);

int (map_vram)(uint16_t mode);

int (vg_draw_hline)(uint16_t x, uint16_t line, uint16_t width, uint32_t color);

int(vg_draw_rectangle)(uint16_t x, uint16_t y,uint16_t width, uint16_t height,uint32_t color);

int(vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

int(vg_draw_xpm_img)(xpm_image_t *xpm_img, uint16_t x, uint16_t y);

int(vg_clear_screen)();

uint8_t (get_rectangles_width)(uint8_t no_rectangles);

uint8_t (get_rectangles_height)(uint8_t no_rectangles);

uint16_t (get_graph_y_res)();

uint16_t (get_graph_x_res)();

#endif
