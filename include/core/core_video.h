// Video 

#ifndef CORE_VIDEO
#define CORE_VIDEO

#include "core_memdef.h"

#define VID_MEM         (u16*)(MEM_VRAM)

//Video modes
#define VMODE_0     0x0
#define VMODE_1     0x1
#define VMODE_2     0x2
#define VMODE_3     0x3
#define VMODE_4     0x4   //Mode 4 Note: can only plot pixels in half or full words. No byte writes allowed!
#define VMODE_5     0x5

//Background modes
#define BG_0    0x100
#define BG_1    0x200
#define BG_2    0x400
#define BG_3    0x800
#define BG_OBJ  0x1000

//Background VRAM defines
#define CHARBLOCK_SIZE      0x4000
#define SCREENBLOCK_SIZE    0x800

//Background control defines
#define BG_PRIORITY(n)      (n << 0) //Value between 0 - 3
#define BG_CHARBLOCK(n)     (n << 2) //Value between 0 - 3
#define BG_MOSAIC           0x40
#define BG_8BPP             0x80
#define BG_SCREENBLOCK(n)   (n << 8) //Value between 0 - 31

#define BG_REG_SIZE_32x32   0x0
#define BG_REG_SIZE_64x32   0x4000
#define BG_REG_SIZE_32x64   0x8000
#define BG_REG_SIZE_64x64   0xC000

#define BG_AFF_SIZE_16x16   0x0
#define BG_AFF_SIZE_32x32   0x4000
#define BG_AFF_SIZE_64x64   0x8000
#define BG_AFF_SIZE_128x128 0xC000

//Sprite mapping layout
#define OBJ_ENABLE_1D       0x40 //Use 1D mapping for sprite memory layout (default is 2D)

// Notes:
// index 0 = transparency
// Each pallet can be used as either: 1 pallet of 8 bits per pixel, or 16 pallets of 4 bits per pixel
#define PAL_BG      (u16*)(MEM_PAL)              //Background pallet starts at 0x05000000 and ends @ 0x050001FF
#define PAL_SPRITE  (u16*)(MEM_PAL+0x200)    //Sprite pallet starts at 0x05000200 and ends @ 0x050003FF

#endif //CORE_VIDEO