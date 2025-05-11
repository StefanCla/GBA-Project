#include "core.h"

u16 key_current = 0, key_previous = 0;

void vsync() //Should be changed to use interrupts
{
    while(REG_VCOUNT >= 160);
    while(REG_VCOUNT < 160);
}

int main()
{
    //Specify background mode
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
    
    //Color some pixels
    const int ScreenWidth = 240;

    VID_MEM[120 + 80 * ScreenWidth] = 0x001F; //Red
    VID_MEM[136 + 80 * ScreenWidth] = 0x03E0; //Blue
    VID_MEM[120 + 96 * ScreenWidth] = 0x7C00; //Green

    while(1)
    {
        vsync();
        key_poll();

        if(key_pressed(KEY_A))
        {
            VID_MEM[136 + 80 * ScreenWidth] = 0xFFFF; //White
        }
        else if(key_released(KEY_A))
        {
            VID_MEM[136 + 80 * ScreenWidth] = 0x03E0; //Blue
        }
    }

    return 0;
}