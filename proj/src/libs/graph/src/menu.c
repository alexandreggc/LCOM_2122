#include <lcom/lcf.h>

#include "menu.h"
#include "rectangle.h"
#include "font.h"
#include "rtc.h"
struct menu {
    rectangle_t **buttons;
    font_t *font;
    uint8_t switchState;
    size_t sz;
};

menu_t* (menu_ctor)(font_t *font, size_t n_buttons){
    menu_t *ret = (menu_t*)malloc(sizeof(menu_t));
    if (ret == NULL) return NULL;
    ret->buttons = (rectangle_t**)malloc(n_buttons * sizeof(rectangle_t*));
    ret->font = font;
    ret->switchState = 0;
    ret->sz = 0;
    return ret;
}

void menu_add_button(menu_t *menu, int16_t x, int16_t y, uint16_t w, uint16_t h, char* phrase){
    menu->buttons[menu->sz++] = rectangle_ctor(x, y, w, h, menu->font, phrase);
}


int (menu_update_state)(menu_t *menu, sprite_t *sp, int click) {
    for(size_t i = 0; i < menu->sz; i++){
        if(rectangle_collide_point(menu->buttons[i], sprite_get_xpos(sp) + sprite_get_width(sp) / 2, sprite_get_ypos(sp) + sprite_get_height(sp) / 2)){
        menu->buttons[i]->color = 0x00ff00ff;
        if(click)
            return i + 1;
        }
        else{
         menu->buttons[i]->color = 0x00ff0000;
        }
    }
    return 0;
}

void (menu_draw)(menu_t *menu) {
    for (size_t i = 0; i < menu->sz; i++){
        rectangle_draw(menu->buttons[i]);
    }
    char* datetime = rtc_get_real_time();
    font_draw_string(menu->font, datetime, 50, 50);
    free(datetime);
}

void (menu_dtor)(menu_t *menu){
    for (size_t i = 0; i < menu->sz; i++){
        rectangle_dtor(menu->buttons[i]);
    }
    free(menu->buttons);
    free(menu->font);
    free(menu);
}
