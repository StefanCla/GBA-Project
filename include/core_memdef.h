// Memory location defines

#ifndef CORE_MEMDEF
#define CORE_MEMDEF

#ifndef __ASM__
#include "core_type.h"
#endif //__ASM__

//Re work code below
#define MEM_IO 0x04000000
#define MEM_VRAM 0x06000000

#define REG_DISPCNT *((vu32*)(MEM_IO+0x0000))
#define VID_MEM ((u16*)MEM_VRAM)

#define DCNT_BG2 0x0400
#define DCNT_MODE3 0x0003
//End rework

#define REG_KEYINPUT *(vu16*)0x04000130
#define REG_VCOUNT *(vu16*)0x04000006

#endif //CORE_MEMDEF