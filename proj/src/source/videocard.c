#include <lcom/lcf.h>

#include "../defines/videocard.h"
#include "../macros/graphics_card_macros.h"

static void *video_mem;
static vbe_mode_info_t vbe_mem_info;
static int bytes_per_pixel;
static int bytes_per_line;




/* Set default text mode */
int (set_graphics_mode)(uint16_t mode) {
  reg86_t r86;
   
  /* Specify the appropriate register values */
  
  memset(&r86, 0, sizeof(r86));	/* zero the structure */

  r86.intno = 0x10; /* BIOS video services */
  r86.ah = 0x4f;    /* Set Video Mode function */
  r86.al = 0x02;    /* 80x25 text mode */
  r86.bx = mode | BIT(14);
  /* Make the BIOS call */

  if( sys_int86(&r86) != OK ) {
    printf("\tvg_exit(): sys_int86() failed \n");
    return 1;
  }

  return OK;
}

int(map_vram)(uint16_t mode){
  struct minix_mem_range mr;
  unsigned int vram_base;  /* VRAM's physical addresss */
  unsigned int vram_size;  /* VRAM's size, but you can use
          the frame-buffer size, instead */
  int r;				   

  /* Use VBE function 0x01 to initialize vram_base and vram_size */
  vbe_get_mode_info(mode,&vbe_mem_info);
  bytes_per_pixel = vbe_mem_info.BytesPerScanLine / vbe_mem_info.XResolution;
  bytes_per_line = vbe_mem_info.BytesPerScanLine;
  vram_base = vbe_mem_info.PhysBasePtr;
  vram_size = bytes_per_pixel * vbe_mem_info.XResolution * vbe_mem_info.YResolution;

  /* Allow memory mapping */

  mr.mr_base = (phys_bytes) vram_base;	
  mr.mr_limit = mr.mr_base + vram_size;

  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);

  /* Map memory */

  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

  if(video_mem == MAP_FAILED)
    panic("couldn't map video memory");
  
return OK;

}

int(vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color){
  int pos = y * bytes_per_line + x*bytes_per_pixel;
  memcpy((void*)((unsigned int)video_mem + pos), &color, bytes_per_pixel);
  return OK;
} 

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){
  for(uint16_t col = x; col < x + len; col++){
    vg_draw_pixel(col,y,color);
  }
  return OK;
}

int(vg_draw_rectangle)(uint16_t x, uint16_t y,uint16_t width, uint16_t height,uint32_t color){
  for(uint16_t line = y; line < y + height; line++){
    vg_draw_hline(x,line, width, color);
  }
  return OK;
}


int(vg_draw_xpm_img)(xpm_image_t *xpm_img, uint16_t x, uint16_t y){
  int Xres = vbe_mem_info.XResolution;
  int Yres = vbe_mem_info.YResolution;
  for (int w = 0; w < xpm_img->width; w++) {
        for (int h = 0; h < xpm_img->height; h++) {
            if (x + w < Xres && y + h < Yres) {
                vg_draw_pixel(x + w, y + h, xpm_img->bytes[w + h * xpm_img->width]);
            }
        }
    }
  return OK;
}


int(vg_clear_screen)(){
  vg_draw_rectangle(0,0,vbe_mem_info.XResolution, vbe_mem_info.YResolution, BLACK);
  return OK;
}

uint8_t (get_rectangles_width)(uint8_t no_rectangles){
  return vbe_mem_info.XResolution / no_rectangles;
}

uint8_t (get_rectangles_height)(uint8_t no_rectangles){
    return vbe_mem_info.YResolution / no_rectangles;
}

vbe_mode_info_t getModeInfo(){
  return vbe_mem_info;
}
