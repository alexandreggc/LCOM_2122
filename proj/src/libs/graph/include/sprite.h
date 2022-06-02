#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

typedef struct sprite sprite_t;

sprite_t* (sprite_constructor)(const char *const *xpm);
void (sprite_destructor)(sprite_t *sp);

int (sprite_get_width)(sprite_t *sp);
int (sprite_get_height)(sprite_t *sp);
int (sprite_get_xpos)(sprite_t *sp);
int (sprite_get_ypos)(sprite_t *sp);
int (sprite_get_xspeed)(sprite_t *sp);
int (sprite_get_yspeed)(sprite_t *sp);

void (sprite_set_pos)(sprite_t *sp, int x, int y);
void(sprite_set_speed)(sprite_t *sp, int vx, int vy);
void (sprite_draw)(sprite_t *sp);

#endif
