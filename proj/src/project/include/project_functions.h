#ifndef PROJ_FUNCTIONS_H_INCLUDED
#define PROJ_FUNCTIONS_H_INCLUDED

#include <lcom/lcf.h>

#include <lcom/proj.h>

#include "videocard.h"
#include "keyboard.h"
#include "mouse.h"
#include "timer.h"
#include "utils.h"
#include "project_macros.h"

int playerMove(uint8_t x, uint8_t y);

int getInitialPos(uint8_t *pos[2]);




#endif
