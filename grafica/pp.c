// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <pp.h>

#include <stdint.h>

// Any header files included below this line should have been created by you

u_int8_t video_mem;
lpv_mode_info_t info;


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/pp/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/pp/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color){
    int pos = y * info.bpp * info.x_res + x * info.bpp;
    memcpy((void*)((unsigned int)video_mem + pos), &color, info.bpp);
    return 0;
} 

int (pp_test_line)(uint8_t mode, enum lpv_dir_t dir, uint16_t x, uint16_t y, uint16_t len, uint32_t color, uint32_t delay){
    if(lpv_set_mode(mode)){
        return 1;
    }

    if(lpv_get_mode_info(mode, &info)){
        return 1;
    }
    video_mem = video_map_phys(info.phys_addr, info.x_res * info.y_res * info.bpp);

    if(dir == lpv_hor){
        for(int x_axis = x; x_axis < x + len; x_axis++){
            if(x_axis < info.h_res && x_axis > 0)
                vg_draw_pixel(x_axis, y, color);
        }
    }

    else if(dir == lpv_vert){
        for(int y_axis = y; y_axis < y + len; y_axis++){
            if(y_axis < info.v_res && y_axis > 0)
                vg_draw_pixel(x, y_axis, color);
        }
    }
    sleep(delay * 1000000);

if(lpv_set_mode(0)){
        return 1;
    }
    return 0;
}