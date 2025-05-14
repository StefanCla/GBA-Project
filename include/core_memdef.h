// Memory location defines

#ifndef CORE_MEMDEF
#define CORE_MEMDEF

#ifndef __ASM__
#include "core_type.h"
#endif //__ASM__

//Hardware memory map
#define MEM_EWRAM   0x02000000  // Ends @ 0x0203FFFF | External Work memory [16 bit bus, prefer THUMB]
#define MEM_IWRAM   0x03000000  // Ends @ 0x03007FFF | Internal Work memory [32 bit bus, prefer ARM]
#define MEM_IO      0x04000000  // Ends @ 0x040003FF | Graphics, sounds, button & others [16 bit bus, prefer THUMB]
#define MEM_PAL     0x05000000  // Ends @ 0x050003FF | Color pallet [16 bit bus, prefer THUMB]
#define MEM_VRAM    0x06000000  // Ends @ 0x06017FFF | Video memory [16 bit bus, prefer THUMB]
#define MEM_OAM     0x07000000  // Ends @ 0x070003FF | Sprite control [32 bit bus, prefer ARM]
#define MEM_PAK     0x08000000  // Game rom [16 bit bus, prefer THUMB]
#define MEM_SAV     0x0E000000  // Save data, length isn't fixed but 64KB is good indication. 8 bit write bus

//Access above memory map
#define VID_MEM ((u16*)MEM_VRAM)

#endif //CORE_MEMDEF