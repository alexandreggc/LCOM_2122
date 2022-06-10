#include <lcom/lcf.h>

#include "font.h"

struct font {
    sprite_t **glyphs;
    size_t sz;
};

font_t* (font_ctor)(){
    font_t *ret = (font_t*)malloc(sizeof(font_t));
    if (ret == NULL) return NULL;
    ret->sz = NUM_SYMBOLS;
    ret->glyphs = (sprite_t**)malloc((ret->sz * sizeof(sprite_t*)));
    font_load_glyphs(ret);
    return ret;
}

void (font_load_glyphs)(font_t *font){
  for(size_t i = 44; i <= font->sz; i++){
    switch (i)
    {
    case 44:{
      font->glyphs[i] = sprite_constructor((const char* const*)char44_xpm);
      break;
    }
    case 46:{
      font->glyphs[i] = sprite_constructor((const char* const*)char46_xpm);
      break;
    }
    case 48:{
      font->glyphs[i] = sprite_constructor((const char* const*)char48_xpm);
      break;
    }
    case 49:{
      font->glyphs[i] = sprite_constructor((const char* const*)char49_xpm);
      break;
    }
    case 50:{
      font->glyphs[i] = sprite_constructor((const char* const*)char50_xpm);
      break;
    }
    case 51:{
      font->glyphs[i] = sprite_constructor((const char* const*)char51_xpm);
      break;
    }
    case 52:{
      font->glyphs[i] = sprite_constructor((const char* const*)char52_xpm);
      break;
    }
    case 53:{
      font->glyphs[i] = sprite_constructor((const char* const*)char53_xpm);
      break;
    }
    case 54:{
      font->glyphs[i] = sprite_constructor((const char* const*)char54_xpm);
      break;
    }
    case 55:{
      font->glyphs[i] = sprite_constructor((const char* const*)char55_xpm);
      break;
    }
    case 56:{
      font->glyphs[i] = sprite_constructor((const char* const*)char56_xpm);
      break;
    }
    case 57:{
      font->glyphs[i] = sprite_constructor((const char* const*)char57_xpm);
      break;
    }
    case 58:{
      font->glyphs[i] = sprite_constructor((const char* const*)char58_xpm);
      break;
    }
    case 65:{
      font->glyphs[i] = sprite_constructor((const char* const*)char65_xpm);
      break;
    }
    case 66:{
      font->glyphs[i] = sprite_constructor((const char* const*)char66_xpm);
      break;
    }
    case 67:{
      font->glyphs[i] = sprite_constructor((const char* const*)char67_xpm);
      break;
    }
    case 68:{
      font->glyphs[i] = sprite_constructor((const char* const*)char68_xpm);
      break;
    }
    case 69:{
      font->glyphs[i] = sprite_constructor((const char* const*)char69_xpm);
      break;
    }
    case 70:{
      font->glyphs[i] = sprite_constructor((const char* const*)char70_xpm);
      break;
    }
    case 71:{
      font->glyphs[i] = sprite_constructor((const char* const*)char71_xpm);
      break;
    }
    case 72:{
      font->glyphs[i] = sprite_constructor((const char* const*)char72_xpm);
      break;
    }
    case 73:{
      font->glyphs[i] = sprite_constructor((const char* const*)char73_xpm);
      break;
    }
    case 74:{
      font->glyphs[i] = sprite_constructor((const char* const*)char74_xpm);
      break;
    }
    case 75:{
      font->glyphs[i] = sprite_constructor((const char* const*)char75_xpm);
      break;
    }
    case 76:{
      font->glyphs[i] = sprite_constructor((const char* const*)char76_xpm);
      break;
    }
    case 77:{
      font->glyphs[i] = sprite_constructor((const char* const*)char77_xpm);
      break;
    }
    case 78:{
      font->glyphs[i] = sprite_constructor((const char* const*)char78_xpm);
      break;
    }
    case 79:{
      font->glyphs[i] = sprite_constructor((const char* const*)char79_xpm);
      break;
    }
    case 80:{
      font->glyphs[i] = sprite_constructor((const char* const*)char80_xpm);
      break;
    }
    case 81:{
      font->glyphs[i] = sprite_constructor((const char* const*)char81_xpm);
      break;
    }
    case 82:{
      font->glyphs[i] = sprite_constructor((const char* const*)char82_xpm);
      break;
    }
    case 83:{
      font->glyphs[i] = sprite_constructor((const char* const*)char83_xpm);
      break;
    }
    case 84:{
      font->glyphs[i] = sprite_constructor((const char* const*)char84_xpm);
      break;
    }
    case 85:{
      font->glyphs[i] = sprite_constructor((const char* const*)char85_xpm);
      break;
    }
    case 86:{
      font->glyphs[i] = sprite_constructor((const char* const*)char86_xpm);
      break;
    }
    case 87:{
      font->glyphs[i] = sprite_constructor((const char* const*)char87_xpm);
      break;
    }
    case 88:{
      font->glyphs[i] = sprite_constructor((const char* const*)char88_xpm);
      break;
    }
     case 89:{
      font->glyphs[i] = sprite_constructor((const char* const*)char89_xpm);
      break;
    }
     case 90:{
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
    if((code = phrase[i]) == SPACE_BAR_CODE){
      x += sprite_get_width(font->glyphs[65]);
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
  return sprite_get_width(font->glyphs[65]);
}

int (font_get_char_height)(font_t *font){
  return sprite_get_height(font->glyphs[65]);
}
