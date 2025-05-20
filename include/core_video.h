// Video 

#ifndef CORE_VIDEO
#define CORE_VIDEO

#include "core_memdef.h"

#define REG_DISPCNT     *(vu32*)(MEM_IO)            //Display control register
#define REG_DISPSTAT    *(vu32*)(MEM_IO+0x0004)     //Display stats register
#define REG_VCOUNT      *(vu32*)(MEM_IO+0x0006)     //Vertical scanline counter

#define VID_MEM (u16*)(MEM_VRAM)

//Video modes
#define VMODE_0     0
#define VMODE_1     1
#define VMODE_2     2
#define VMODE_3     3
#define VMODE_4     4   //Mode 4 Note: can only plot pixels in half or full words. No byte writes allowed!
#define VMODE_5     5

//Background modes
#define BG_0    256
#define BG_1    512
#define BG_2    1024
#define BG_3    2048
#define BG_OBJ  4096

// Notes:
// index 0 = transparency
// Each pallet can be used as either: 1 pallet of 8 bits per pixel, or 16 pallets of 4 bits per pixel
#define PAL_BG MEM_PAL              //Background pallet starts at 0x05000000 and ends @ 0x050001FF
#define PAL_SPRITE MEM_PAL+0x200    //Sprite pallet starts at 0x05000200 and ends @ 0x050003FF




#endif //CORE_VIDEO