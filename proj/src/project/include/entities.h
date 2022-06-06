#ifndef ENTITIES_H_INCLUDED
#define ENTITIES_H_INCLUDED

enum element_t{
  PLAYER,
  ENEMY,
  WALL,
  WOOD
};


// WALL FUNCTIONS

typedef struct wall wall_t;

wall_t* (wall_constructor)(int x, int y);
void (wall_destructor)(wall_t* wall);
void (wall_draw)(wall_t* w);
bool (wall_broken)(wall_t* w);
int (wall_get_xmap)(wall_t* w);
int (wall_get_ymap)(wall_t* w);
void (wall_set_broken)(wall_t* w);


// MAP FUNCTIONS

typedef struct map map_t;

map_t* (map_constructor)(const char *const *xpm);
void (map_destructor)(map_t *map);
void (map_draw)(map_t *map);

#endif
