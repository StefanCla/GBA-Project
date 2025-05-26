#include <string.h>
#include "core.h"
#include "sprites/metroid.h"

u16 key_current = 0, key_previous = 0;
const u32 MAX_OBJECT_REG = 128;
OBJ_ATTRIBUTE obj_buffer[128];

//Objects must be initialized before they can be shown on screen
void init_objects()
{
	u32* obj = (u32*)obj_buffer;

	u32 count = MAX_OBJECT_REG;
	while(count--)
	{
		*obj++ = 0x0200; //Set attribute0 to hide sprites
		*obj++ = 0;
	}

	memcpy((OBJ_ATTRIBUTE*)MEM_OAM, obj, sizeof(obj_buffer));
}

void vsync() //Should be changed to use interrupts
{
    while(REG_VCOUNT >= 160);
    while(REG_VCOUNT < 160);
}

int main()
{
	//Copy data into vraM & pallete
	memcpy(VRAM_BLOCK_4, metroidTiles, metroidTilesLen);
	memcpy(PAL_SPRITE, metroidPal, metroidPalLen);

	init_objects();

	REG_DISPCNT= BG_OBJ | OBJ_ENABLE_1D;

	//Set OAM data
	OBJ_ATTRIBUTE* object1 = &obj_buffer[0];
	object1->attrib0 = 0;
	object1->attrib1 = 0xC000;	//We use 64x64 sprite
	object1->attrib2 = 0;

	memcpy((OBJ_ATTRIBUTE*)MEM_OAM, object1, sizeof(OBJ_ATTRIBUTE));

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

		memcpy((OBJ_ATTRIBUTE*)MEM_OAM, object1, sizeof(OBJ_ATTRIBUTE));
	}

	return 0;
}