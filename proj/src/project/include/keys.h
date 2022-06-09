#ifndef KEYS_H_INCLUDED
#define KEYS_H_INCLUDED

#include <lcom/lcf.h>
#include "keys.h"



typedef struct keys keys_t;
struct keys{
    uint8_t up_pressed;
    uint8_t left_pressed;
    uint8_t down_pressed;
    uint8_t right_pressed;
    uint8_t space_pressed;
};


keys_t* (keys_ctor)();

void (keys_dtor)(keys_t *keys);

void(clear_keys)(keys_t *keys);


#endif
