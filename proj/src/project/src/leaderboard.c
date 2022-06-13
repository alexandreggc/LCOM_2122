#include <lcom/lcf.h>

#include "leaderboard.h"
#include "font.h"

struct leaderboard {
    font_t *font;
    char* file_location;
};

struct entry {
    int seconds;
    char* line;
};

void (entry_destructor)(entry_t* entry){
  free(entry->line);
  free(entry);
}

entry_t*(entry_constructor)(int time, char* line){
  entry_t *ret = malloc(sizeof(entry_t));
  ret->seconds = time;
  ret->line = malloc(sizeof(char)*100);
  strcpy(ret->line, line);
  //ret->line = line;
  return ret;
}

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
  strcat(timeCounterString," S");

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

int cmpfunc (const void * a, const void * b) {
  entry_t *a1 = *(entry_t**)a;
  entry_t *b1 = *(entry_t**)b;
  return ( a1->seconds - b1->seconds );
}

void(leaderboard_sort_entries)(leaderboard_t *lb){

  FILE *file = fopen(lb->file_location, "r");

  char *line = malloc(sizeof(char)*100);
  entry_t** entries = malloc(sizeof(entry_t*));
  int size = 0;

  while(fscanf(file, "%[^\n] ", line) != EOF) {
    char name[100]; char rest[100]; char time[100];

    sscanf(line, "%15[^\n] %s %s", name, time, rest);
    int t = atoi(time);

    entries[size] = entry_constructor(t,line);
    size++;
    entries = realloc(entries, sizeof(entry_t*)*(size+1));
  }

  free(line);
  fclose(file);

  qsort(entries, size, sizeof(entry_t*), &cmpfunc);

  file = fopen(lb->file_location, "w");
  for(int j=0 ; j<size; j++){
    fprintf(file, "%s\n", entries[j]->line);
  }
  fclose(file);

  for(int l=1 ; l<size; l++){
    entry_destructor(entries[l]);
  }
  free(entries);
}
