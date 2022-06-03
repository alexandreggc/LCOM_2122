#include <lcom/lcf.h>

#include "sprite.h"
#include "videocard.h"
#include <stdio.h>

struct sprite{
  int x, y; // current position
  int width, height; // dimensions
  int xspeed, yspeed; // current speed
  xpm_image_t *img; // the pixmap
};

sprite_t* (sprite_constructor)(const char *const *xpm){
  sprite_t* ret = malloc(sizeof(sprite_t));
  xpm_image_t *xpm_img = malloc(sizeof(xpm_image_t));
  if (ret==NULL || xpm_img==NULL) return NULL;
  uint8_t *map = xpm_load((xpm_map_t)xpm, XPM_INDEXED, xpm_img);
  if (map == NULL) sprite_destructor(ret);
  xpm_img->bytes=map;
  ret->img = xpm_img;
  ret->height = xpm_img->height;
  ret->width = xpm_img->width;
  ret->x=0; ret->y=0;
  return ret;
}

void (sprite_destructor)(sprite_t *sp){
  if (sp == NULL) return;
  free(sp->img);
  free(sp);
}


int (sprite_get_width)(sprite_t *sp){
  return sp->width;
}
int (sprite_get_height)(sprite_t *sp){
  return sp->height;
}
int (sprite_get_xpos)(sprite_t *sp){
  return sp->x;
}
int (sprite_get_ypos)(sprite_t *sp){
  return sp->y;
}
int (sprite_get_xspeed)(sprite_t *sp){
  return sp->xspeed;
}
int (sprite_get_yspeed)(sprite_t *sp){
  return sp->yspeed;
}

void (sprite_set_pos)(sprite_t *sp, int x, int y){
  sp->x = x; sp->y = y;
}
void(sprite_set_speed)(sprite_t *sp, int vx, int vy){
  sp->xspeed = vx; sp->yspeed = vy;
}

void (sprite_draw)(sprite_t *sp){
  vg_draw_xpm_img(sp->img , sp->x, sp->y);
}

void (sprite_update_pos)(sprite_t *sp){
  if(sp->x + sp->xspeed >= 0 && sp->x + sp->xspeed + sp->width <= get_graph_x_res())
    sp->x += sp->xspeed;
  if(sp->y + sp->yspeed >= 0 && sp->y + sp->xspeed + sp->width <= get_graph_y_res())
    sp->y += sp->yspeed;
}
