#include "project_functions.h"


int playerMove(uint8_t x, uint8_t y){
    *pos += x;
    *(pos + 1) += y;
    return 0;
}

int getInitialPos(uint8_t *pos[2]){
    *pos = 20;
    *(pos + 1) = 30;
    return 0;
}

int getPos(uint8_t *pos[2]){
    *pos[2] = pos;
}