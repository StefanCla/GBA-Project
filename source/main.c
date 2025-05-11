#include "core.h"

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