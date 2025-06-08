// Memory location defines

#ifndef CORE_MEMDEF
#define CORE_MEMDEF

#ifndef __ASM__
#include "core_type.h"
#endif //__ASM__

//Hardware memory map
#define MEM_EWRAM   0x02000000  // Ends @ 0x0203FFFF | External Work memory [16 bit bus, prefer THUMB]
#define MEM_IWRAM   0x03000000  // Ends @ 0x03007F00 | Internal Work memory [32 bit bus, prefer ARM] (0x03007F00 - 0x03007FFF is used for internal bios)
#define MEM_IO      0x04000000  // Ends @ 0x040003FF | Graphics, sounds, button & others [16 bit bus, prefer THUMB]
#define MEM_PAL     0x05000000  // Ends @ 0x050003FF | Color pallet [16 bit bus, prefer THUMB]
#define MEM_VRAM    0x06000000  // Ends @ 0x06017FFF | Video memory [16 bit bus, prefer THUMB]
#define MEM_OAM     0x07000000  // Ends @ 0x070003FF | Sprite control [32 bit bus, prefer ARM]
#define MEM_PAK     0x08000000  // Game rom [16 bit bus, prefer THUMB]
#define MEM_SAV     0x0E000000  // Save data, length isn't fixed but 64KB is good indication. 8 bit write bus


//Although not a memory map, registers will also be located here

//Registers
//Display
#define REG_DISPCNT     *(vu16*)(MEM_IO)            // Display control register
#define REG_DISPSTAT    *(vu16*)(MEM_IO + 0x0004)   // Display stats register
#define REG_VCOUNT      *(vu16*)(MEM_IO + 0x0006)   // Vertical scanline counter

//Background
#define REG_BG0CNT      *(vu16*)(MEM_IO + 0x0008)   //Background control for background 0
#define REG_BG1CNT      *(vu16*)(MEM_IO + 0x000A)   //Background control for background 1
#define REG_BG2CNT      *(vu16*)(MEM_IO + 0x000C)   //Background control for background 2
#define REG_BG3CNT      *(vu16*)(MEM_IO + 0x000E)   //Background control for background 3

//Background offset | Can't be read, only written too
#define REG_BG0HOFS     *(vu16*)(MEM_IO + 0x0010)   //X offset (horizontal) for BG0
#define REG_BG0VOFS     *(vu16*)(MEM_IO + 0x0012)   //Y offset (vertical) for BG0
#define REG_BG1HOFS     *(vu16*)(MEM_IO + 0x0014)   //X offset (horizontal) for BG1
#define REG_BG1VOFS     *(vu16*)(MEM_IO + 0x0016)   //Y offset (vertical) for BG1
#define REG_BG2HOFS     *(vu16*)(MEM_IO + 0x0018)   //X offset (horizontal) for BG2
#define REG_BG2VOFS     *(vu16*)(MEM_IO + 0x001A)   //Y offset (vertical) for BG2
#define REG_BG3HOFS     *(vu16*)(MEM_IO + 0x001C)   //X offset (horizontal) for BG3
#define REG_BG3VOFS     *(vu16*)(MEM_IO + 0x001E)   //Y offset (vertical) for BG3


//Input
#define REG_KEYINPUT    *(vu16*)(MEM_IO + 0x0130)   //Key input register - Used for keypresses
#define REG_KEYCNT      *(vu16*)(MEM_IO + 0x0132)   //Key control register - Used for key interrupts

//Other
#define VRAM_BLOCK_4    (u32*)(MEM_VRAM + 0x010000)    //Block 4 | Beginning of sprite location
#define VRAM_BLOCK_5    (u32*)(MEM_VRAM + 0x014000)    //Block 5 | Last block of sprite location

#endif //CORE_MEMDEF