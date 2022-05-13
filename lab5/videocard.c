#include <lcom/lcf.h>

#include "videocard.h"

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
