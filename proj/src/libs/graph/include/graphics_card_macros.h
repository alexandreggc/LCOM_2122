#ifndef GRAPHICS_CARD_MACROS_H_INCLUDED
#define GRAPHICS_CARD_MACROS_H_INCLUDED
/**
 * @defgroup videocard videocard
 * @{
 */
// Graphics modes
#define INDEXED_1024_768        0x105
#define DIRECT_640_480          0x110
#define DIRECT_800_600          0x115
#define DIRECT_1280_1024_565    0x11A
#define DIRECT_1280_1024_888    0x11B
#define LINEAR_FRAME_BUFFER_MD  BIT(14)


#define GET_RED(n)          (0xFF & ((n) >> 16))
#define GET_GRE(n)          (0xFF & ((n) >>  8))
#define GET_BLU(n)          (0xFF & (n))
#define SET_RED(n)          (((n)&0xFF) << 16)
#define SET_GRE(n)          (((n)&0xFF) <<  8)
#define SET_BLU(n)          (((n)&0xFF))
#define SET_COLOR(r,g,b)    (SET_RED(r) | SET_GRE(g) | SET_BLU(b))


// Colors
#define BLACK 0x00
/**
 * @}
 */
#endif
