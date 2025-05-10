#define MEM_IO 0x04000000
#define MEM_VRAM 0x06000000

#define REG_DISPCNT *((volatile unsigned int*)(MEM_IO+0x0000))
#define VID_MEM ((unsigned short*)MEM_VRAM)

#define DCNT_BG2 0x0400
#define DCNT_MODE3 0x0003

int main()
{
    //Initial project setup code

    //Specify background mode
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
    
    //Color some pixels
    const int ScreenWidth = 240;

    VID_MEM[120 + 80 * ScreenWidth] = 0x001F; //Red
    VID_MEM[136 + 80 * ScreenWidth] = 0x03E0; //Blue
    VID_MEM[120 + 96 * ScreenWidth] = 0x7C00; //Green

    while(1);

    return 0;
}