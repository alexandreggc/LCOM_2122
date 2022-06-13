#include <lcom/lcf.h>

#include "rectangle.h"
#include "font.h"


rectangle_t* (rectangle_ctor)(int16_t x, int16_t y, uint16_t w, uint16_t h, font_t *font, char* phrase){
    rectangle_t *ret = (rectangle_t*)malloc(sizeof(rectangle_t));
    if(ret == NULL) return NULL;
    ret->x = x;
    ret->y = y;
    ret->w = w;
    ret->h = h;
    ret->font = font;
    ret->phrase = phrase;
    ret->color = 0x00ff0000;
    return ret;
}
void (rectangle_dtor)(rectangle_t *rectangle){free(rectangle);}
void (rectangle_set_pos)(rectangle_t *p, int16_t x, int16_t y){ p->x = x; p->y = y; }
void (rectangle_set_size)(rectangle_t *p, uint16_t w, uint16_t h){ p->w = w; p->h = h; }
void (rectangle_set_color)(rectangle_t *p, uint32_t color){ p->color = color; }

int16_t  (rectangle_get_x)(const rectangle_t *p){ return p->x; }
int16_t  (rectangle_get_y)(const rectangle_t *p){ return p->y; }
uint16_t (rectangle_get_w)(const rectangle_t *p){ return p->w; }
uint16_t (rectangle_get_h)(const rectangle_t *p){ return p->h; }

int (rectangle_collide_point)(const rectangle_t *p, int x, int y) {
    return (x >= p->x && x <= p->x + p->w) && (y >= p->y && y <= p->y + p->h);
}

void (rectangle_draw)(rectangle_t *p){
    vg_draw_rectangle(p->x, p->y, p->w, p->h, p->color);
    font_draw_string(p->font, p->phrase, rectangle_draw_start_x(p), rectangle_draw_start_y(p));
}

int (rectangle_draw_start_x)(rectangle_t *p){
    return p->x + p->w/2 - (strlen(p->phrase)/2) * font_get_char_width(p->font);
}

int (rectangle_draw_start_y)(rectangle_t *p){
    return p->y + p->h/2 - font_get_char_height(p->font) / 2;
}
