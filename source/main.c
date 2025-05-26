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
		*obj++ = ATTRIB0_HIDE; //Set attribute0 to hide sprites
		*obj++ = 0;
	}

	memcpy((OBJ_ATTRIBUTE*)MEM_OAM, obj, sizeof(obj_buffer));
}

void set_object_position(OBJ_ATTRIBUTE* object, u32 x, u32 y)
{
	//We zero-out the first 8 bits of attribute 0, and set the first 8 bits of Y into the attribute
	object->attrib0 = (object->attrib0 & ~OBJ_Y_MASK) | (y & OBJ_Y_MASK);

	//Same but with  9 bits
	object->attrib1 = (object->attrib1 & ~OBJ_X_MASK) | (x & OBJ_X_MASK);
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
	object1->attrib1 = ATTRIB1_SIZE_64x64;	//We use 64x64 sprite
	object1->attrib2 = 0;

	memcpy((OBJ_ATTRIBUTE*)MEM_OAM, object1, sizeof(OBJ_ATTRIBUTE));

	s32 x = 10, y = 10;

	while(1)
	{
		vsync();
		key_poll();

		//Not used this time
		if(key_pressed(KEY_LEFT) || key_held(KEY_LEFT))
		{
			x += -1;
		}
		else if(key_pressed(KEY_RIGHT) || key_held(KEY_RIGHT))
		{
			x += 1;
		}

        if(key_pressed(KEY_UP) || key_held(KEY_UP))
        {
			y += -1;
        }
        else if(key_pressed(KEY_DOWN) || key_held(KEY_DOWN))
        {
			y += 1;
        }

		set_object_position(object1, x, y);
		memcpy((OBJ_ATTRIBUTE*)MEM_OAM, object1, sizeof(OBJ_ATTRIBUTE));
	}

	return 0;
}