#ifndef ENTITIES_H_INCLUDED
#define ENTITIES_H_INCLUDED

typedef struct map map_t;


enum element_t{
  PLAYER,
  ENEMY,
  WALL,
  WOOD
};


map_t* (map_constructor)(const char *const *xpm);

void (map_destructor)(map_t *map);

#endif
