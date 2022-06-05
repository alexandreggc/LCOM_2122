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
    font_load_glyphs(ret);
    return ret;
}

void (font_load_glyphs)(font_t *font){
  for(size_t i = 0; i < font->sz; i++){
    switch (i)
    {
    case 0:{
      font->glyphs[i] = sprite_constructor((const char* const*)char65_xpm);
      break;
    }
    case 1:{
      font->glyphs[i] = sprite_constructor((const char* const*)char66_xpm);
      break;
    }
    default:
      break;
    }
  }
}

void (font_draw_string)(font_t *font, char *phrase, uint16_t x, uint16_t y){
  for(size_t i = 0; i < strlen(phrase); i++){
    sprite_set_pos(font->glyphs[phrase[i] - 65], x, y);
    sprite_draw(font->glyphs[phrase[i] - 65]);
    x += sprite_get_width(font->glyphs[phrase[i] - 65]);
  }
}


void (font_dtor)(font_t *font){
  for(size_t i = 0; i < font->sz; i++){
    sprite_destructor(font->glyphs[i]);
  }
  free(font->glyphs);
}
