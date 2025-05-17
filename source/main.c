#include "core.h"

u16 key_current = 0, key_previous = 0;	

void vsync() //Should be changed to use interrupts
{
    while(REG_VCOUNT >= 160);
    while(REG_VCOUNT < 160);
}

int main()
{
    //Drawing two full pages in Mode 4, and flip between them.
    REG_DISPCNT = VMODE_4 | BG_2;

    const u32 MAX_WIDTH = 240;
    const u32 MAX_HEIGHT = 160;
    const u32 MAX_MODE3_SIZE = 0x12C00;
    const u32 MAX_MODE4_SIZE = 0x9600;

    u8 ColorOne = 0x00; //Black
    u8 ColorTwo = 0x00; //Black

    u16* Pal = (u16*)PAL_BG;

    //Combine 2 colors to one for faster writing
    u16 NewColor = ((ColorOne << 8) | ColorTwo);

    //Page flipping setup
    u16* FrontPage = VID_MEM;
    u16* BackPage = VID_MEM + 0xA000;
    bool bIsFront = true;
    u32* Dest = (u32*)FrontPage;

    while(1)
    {
        vsync();
        key_poll();

        //Not used this time
        if(key_pressed(KEY_A) || key_held(KEY_A))
        {
        }
        else if(key_released(KEY_A))
        {
        }

        //Flip between pages
        if(bIsFront)
        {
            Dest = (u32*)BackPage;
            REG_DISPCNT = 0x0; //Set 4th bit to indicate what page to use
            ColorOne = 0xFF;
            ColorTwo = 0xFF;
            bIsFront = false;
        }
        else if(!bIsFront)
        {
            Dest = (u32*)FrontPage;
            REG_DISPCNT = 0xF;  //Set 4th bit to indicate what page to use
            ColorOne = 0x00;
            ColorTwo = 0x00;
            bIsFront = true;
        }

        NewColor = (ColorOne << 24) | (ColorTwo << 16) | (ColorOne << 8) | ColorTwo;
        *Pal = NewColor;

        for(u32 i = 0; i < MAX_MODE4_SIZE; i++)
        {
            *Dest++ = NewColor;
        }
    }

    return 0;
}