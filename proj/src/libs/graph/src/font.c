#include <lcom/lcf.h>

#include "font.h"

struct font {
    sprite_t **glyphs;
    size_t sz;
};

font_t* (font_ctor)(size_t sz){
    font_t *ret = (font_t*)malloc(sizeof(font_t));
    if (ret == NULL) return NULL;
    ret->sz = sz;
    ret->glyphs = (sprite_t**)malloc((ret->sz * sizeof(sprite_t*)));
    return ret;
}

void (font_load_glyphs)(font_t *font){
  for(size_t i = 0; i < font->sz; i++){
    font->glyphs[i] = sprite_constructor((const char* const*)char65_xpm); // um xpm para cada -> fazer switch (i)
  }
}

void (font_draw_string)(font_t *font, char *string, size_t sz, uint16_t x, uint16_t y){
  for(size_t i = 0; i < sz; i++){
    sprite_set_pos(font->glyphs[(int)string[(int)i] - 65], x, y);
    sprite_draw(font->glyphs[(int)string[(int)i] - 65]);
    x += sprite_get_width(font->glyphs[(int)string[i] - 65]);
  }
}


void (font_dtor)(font_t *font){
  for(size_t i = 0; i < font->sz; i++){
    sprite_destructor(font->glyphs[i]);
  }
  free(font->glyphs);
}
