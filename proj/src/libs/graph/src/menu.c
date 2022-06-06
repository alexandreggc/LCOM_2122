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
    ret->playButton = rectangle_ctor(300,200,200,100);
    ret->exitButton = rectangle_ctor(300,350,200,100);
    ret->switchState = 0;
    return ret;
}

int (menu_update_state)(menu_t *menu, sprite_t *sp, int click) {
    if(rectangle_collide_point(menu->playButton, sprite_get_xpos(sp) + sprite_get_width(sp) / 2, sprite_get_ypos(sp) + sprite_get_height(sp) / 2)){
        menu->playButton->color = 0x00ff00ff;
        if(click)
            return 1;
    }
    else{
         menu->playButton->color = 0x00ff0000;
    }
    if(rectangle_collide_point(menu->exitButton, sprite_get_xpos(sp)+ sprite_get_width(sp) / 2 , sprite_get_ypos(sp) + sprite_get_height(sp) / 2)){
         menu->exitButton->color = 0x00ff00ff;
        if(click)
            return 2;
    }
    else{
        menu->exitButton->color = 0x00ff0000;
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
