#include "core.h"

u16 key_current = 0, key_previous = 0;

void vsync() //Should be changed to use interrupts
{
    while(REG_VCOUNT >= 160);
    while(REG_VCOUNT < 160);
}

int main()
{
    //Drawing square using mode 3 bitmaps
    REG_DISPCNT = VMODE_3 | BG_2;

    u16 Color = 0xFFFF; //White
    const u32 MAX_WIDTH = 240;
    const u32 MAX_HEIGHT = 160;

    while(1)
    {
        vsync();
        key_poll();

        if(key_pressed(KEY_A))
        {
            Color = 0x9999; //Orange
        }
        else if(key_released(KEY_A))
        {
            Color = 0xFFFF; //White
        }

        //Create square
        for(u32 i = 0; i < MAX_WIDTH; i++)
        {
            VID_MEM[(i)] = Color;
            VID_MEM[(MAX_HEIGHT - 1) * MAX_WIDTH + i] = Color;
        }

        for(u32 i = 1; i < MAX_HEIGHT; i++)
        {
            VID_MEM[(MAX_WIDTH * i)] = Color;
            VID_MEM[(MAX_WIDTH * i) + (MAX_WIDTH - 1)] = Color;
        }
    }

    return 0;
}