#include <lcom/lcf.h>

enum lpv_dir_t {
    lpv_hor,     // horizontal line
    lpv_vert     // vertical line
};

typedef struct {
    uint16_t x_res;
    uint16_t y_res;
    uint8_t bpp;
    uint8_t r_sz;
    uint8_t r_pos;
    uint8_t g_sz;
    uint8_t g_pos;
    uint8_t b_sz;
    uint8_t b_pos;
    phys_addr_t phys_addr; // video ram base phys address
} lpv_mode_info_t;

int (pp_test_line)(uint8_t mode, enum lpv_dir_t dir, uint16_t x, uint16_t y, uint16_t len, uint32_t color, uint32_t delay);

int(vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);