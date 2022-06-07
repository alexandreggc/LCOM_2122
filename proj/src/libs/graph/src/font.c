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
    case 2:{
      font->glyphs[i] = sprite_constructor((const char* const*)char67_xpm);
      break;
    }
    case 3:{
      font->glyphs[i] = sprite_constructor((const char* const*)char68_xpm);
      break;
    }
    case 4:{
      font->glyphs[i] = sprite_constructor((const char* const*)char69_xpm);
      break;
    }
    case 5:{
      font->glyphs[i] = sprite_constructor((const char* const*)char70_xpm);
      break;
    }
    case 6:{
      font->glyphs[i] = sprite_constructor((const char* const*)char71_xpm);
      break;
    }
    case 7:{
      font->glyphs[i] = sprite_constructor((const char* const*)char72_xpm);
      break;
    }
    case 8:{
      font->glyphs[i] = sprite_constructor((const char* const*)char73_xpm);
      break;
    }
    case 9:{
      font->glyphs[i] = sprite_constructor((const char* const*)char74_xpm);
      break;
    }
    case 10:{
      font->glyphs[i] = sprite_constructor((const char* const*)char75_xpm);
      break;
    }
    case 11:{
      font->glyphs[i] = sprite_constructor((const char* const*)char76_xpm);
      break;
    }
    case 12:{
      font->glyphs[i] = sprite_constructor((const char* const*)char77_xpm);
      break;
    }
    case 13:{
      font->glyphs[i] = sprite_constructor((const char* const*)char78_xpm);
      break;
    }
    case 14:{
      font->glyphs[i] = sprite_constructor((const char* const*)char79_xpm);
      break;
    }
    case 15:{
      font->glyphs[i] = sprite_constructor((const char* const*)char80_xpm);
      break;
    }
    case 16:{
      font->glyphs[i] = sprite_constructor((const char* const*)char81_xpm);
      break;
    }
    case 17:{
      font->glyphs[i] = sprite_constructor((const char* const*)char82_xpm);
      break;
    }
    case 18:{
      font->glyphs[i] = sprite_constructor((const char* const*)char83_xpm);
      break;
    }
    case 19:{
      font->glyphs[i] = sprite_constructor((const char* const*)char84_xpm);
      break;
    }
    case 20:{
      font->glyphs[i] = sprite_constructor((const char* const*)char85_xpm);
      break;
    }
    case 21:{
      font->glyphs[i] = sprite_constructor((const char* const*)char86_xpm);
      break;
    }
    case 22:{
      font->glyphs[i] = sprite_constructor((const char* const*)char87_xpm);
      break;
    }
    case 23:{
      font->glyphs[i] = sprite_constructor((const char* const*)char88_xpm);
      break;
    }
     case 24:{
      font->glyphs[i] = sprite_constructor((const char* const*)char89_xpm);
      break;
    }
     case 25:{
      font->glyphs[i] = sprite_constructor((const char* const*)char90_xpm);
      break;
    }
    default:
      break;
    }
  }
}

void (font_draw_string)(font_t *font, char *phrase, uint16_t x, uint16_t y){
  int code;
  for(size_t i = 0; i < strlen(phrase); i++){
    if((code = phrase[i] - 65) == SPACE_BAR_CODE - 65){
      x += sprite_get_width(font->glyphs[0]);
      continue;
    }
    sprite_set_pos(font->glyphs[code], x, y);
    sprite_draw(font->glyphs[code]);
    x += sprite_get_width(font->glyphs[code]);
  }
}


void (font_dtor)(font_t *font){
  for(size_t i = 0; i < font->sz; i++){
    sprite_destructor(font->glyphs[i]);
  }
  free(font->glyphs);
}

int (font_get_char_width)(font_t *font){
  return sprite_get_width(font->glyphs[0]);
}

int (font_get_char_height)(font_t *font){
  return sprite_get_height(font->glyphs[0]);
}
