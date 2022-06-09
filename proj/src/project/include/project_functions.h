#ifndef PROJ_FUNCTIONS_H_INCLUDED
#define PROJ_FUNCTIONS_H_INCLUDED

#include <lcom/lcf.h>
#include <lcom/proj.h>

#include "libs.h"
#include "videocard.h"
#include "keyboard.h"
#include "mouse.h"
#include "timer.h"
#include "rtc.h"
#include "utils.h"
#include "project_macros.h"

enum GameState{MENU, PLAY, EXIT};

int (point_distance)(int x0, int y0, int x, int y);


#endif
