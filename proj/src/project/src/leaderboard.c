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
    char c[50]; int y = 200;
    while((fscanf(file, "%[^\n] ", c) != EOF) && y<=500) {
      font_draw_string(lb->font,c,10,y);
      y+=50;
    }
    free(c);
    fclose(file);
  }
}

void (gameended_draw)(leaderboard_t *lb, char* playerName, bool alive){
  if(alive) {
    font_draw_string(lb->font,"YOU WON",330,100);
    font_draw_string(lb->font,"ENTER YOUR NAME",50,300);
  font_draw_string(lb->font,playerName,50,400);
  } else{
    font_draw_string(lb->font,"YOU LOST",330,100);
  }
  font_draw_string(lb->font,"ESC TO GO BACK TO MENU",150,500);
}

void (leaderboard_save_file)(leaderboard_t *lb, char* playerName, int timeCounter){
  FILE *file = fopen(lb->file_location, "a");

  if(file==NULL) return;

  char* result = playerName;

  char *date = (char *)malloc(14 * sizeof(char));
  rtc_get_date(date);

  char* timeCounterString = "";
  sprintf(timeCounterString, "%d", (timeCounter/REFRESH_RATE));
  strcat(timeCounterString,"S");

  while(strlen(result) != 16){
    strncat(result," ",1);
  }

  strncat(result,timeCounterString,strlen(timeCounterString));

  while((strlen(result)+10) != 36){
    strncat(result," ",1);
  }

  strncat(result,date,10);


  fprintf(file, "%s\n", result);
  free(result);
  free(timeCounterString);
  free(date);
  fclose(file);
}

