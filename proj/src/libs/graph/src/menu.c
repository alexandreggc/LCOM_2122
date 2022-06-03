#include <lcom/lcf.h>
#include "menu.h"
#include "rectangle.h"

struct menu {
    rectangle_t *playButton;
    rectangle_t *exitButton;
    uint8_t switchState;
};

menu_t* (menu_ctor)(){
    menu_t *ret = (menu_t*)malloc(sizeof(menu_t));
    if (ret == NULL) return NULL;
    ret->playButton = rectangle_ctor(400,200,300,150);
    ret->exitButton = rectangle_ctor(400,500,300,150);
    ret->switchState = 0;
    return ret;
}

int (menu_update_state)(menu_t *menu, sprite_t *sp, int click) {
    if(rectangle_collide_point(menu->playButton, sprite_get_xpos(sp), sprite_get_ypos(sp))){
        menu->playButton->color = 3;
        if(click)
            return 1;
    }
    else{
         menu->playButton->color = 4;
    }
    if(rectangle_collide_point(menu->exitButton, sprite_get_xpos(sp), sprite_get_ypos(sp))){
         menu->exitButton->color = 3;
        if(click)
            return 2;
    }
    else{
        menu->exitButton->color = 4;
    }
    return 0;
}

void (menu_draw)(menu_t *menu) {
    rectangle_draw(menu->playButton);
    rectangle_draw(menu->exitButton);
}

void (menu_dtor)(menu_t *menu){
    rectangle_dtor(menu->playButton);
    rectangle_dtor(menu->playButton);
    free(menu);
}
