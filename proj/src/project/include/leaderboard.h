#ifndef LEADERBOARD_H_INCLUDED
#define LEADERBOARD_H_INCLUDED

#include "font.h"

typedef struct leaderboard leaderboard_t;

leaderboard_t* (leaderboard_constructor)(font_t *font);
void (leaderboard_destructor)(leaderboard_t *lb);
void (leaderboard_draw)(leaderboard_t *lb);
void (gameended_draw)(leaderboard_t *lb, char* playerName);
void (leaderboard_save_file)(leaderboard_t *lb, char* playerName);

#endif

