#include "keys.h"

keys_t* (keys_ctor)() {
    keys_t *ret = (keys_t*)malloc(sizeof(keys_t));
    if(ret == NULL) return NULL;
    ret->up_pressed = 0;
    ret->left_pressed = 0;
    ret->down_pressed = 0;
    ret->right_pressed = 0;
    ret->space_pressed = 0;
    return ret;
}

void (keys_dtor)(keys_t *keys){
  free(keys);
}

void(clear_keys)(keys_t *keys){
  keys->up_pressed = 0; keys->left_pressed = 0; keys->down_pressed = 0; keys->right_pressed = 0; keys->space_pressed = 0;
}
