#include <lcom/lcf.h>

#include "leaderboard.h"
#include "font.h"

struct leaderboard {
    font_t *font;
    char* file_location;
};


leaderboard_t* (leaderboard_constructor)(font_t *font){
  leaderboard_t *ret = (leaderboard_t*)malloc(sizeof(leaderboard_t));
  if (ret == NULL) return NULL;
  ret->font = font;
  ret->file_location = "home/lcom/labs/proj/src/leaderboard.txt";
  return ret;
}

void (leaderboard_destructor)(leaderboard_t *lb){
  free(lb);
}

void (leaderboard_draw)(leaderboard_t *lb) {
  font_draw_string(lb->font,"LEADERBOARD",280,100);

  FILE *file = fopen(lb->file_location, "r");

  if(file==NULL) {
    font_draw_string(lb->font,"CANNOT OPEN FILE",280,200);
  } else {
    char c[20]; int y = 200;
    while(fscanf(file, "%[^\n] ", c) != EOF) {
      font_draw_string(lb->font,c,250,y);
      y+=50;
    }
    fclose(file);
  }
}


