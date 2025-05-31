#include <string.h>
#include "core.h"
#include "sprites/emerald.h"

u16 key_current = 0, key_previous = 0;
const u32 MAX_OBJECT_REG = 128;
OBJ_ATTRIBUTE obj_buffer[128];

const u32 SPRITE_SIZE = 16;

//Objects must be initialized before they can be shown on screen
void init_objects()
{
	u32* obj = (u32*)obj_buffer;

	u32 count = MAX_OBJECT_REG;
	while(count--)
	{
		*obj++ = ATTRIB0_HIDE;
		*obj++ = 0;
	}

	memcpy((OBJ_ATTRIBUTE*)MEM_OAM, obj, sizeof(obj_buffer));
}

void set_object_position(OBJ_ATTRIBUTE* object, u32 x, u32 y)
{
	//We zero-out the first 8 bits of attribute 0, and set the first 8 bits of Y into the attribute
	object->attrib0 = (object->attrib0 & ~OBJ_Y_MASK) | (y & OBJ_Y_MASK);

	//Same but with 9 bits & X value
	object->attrib1 = (object->attrib1 & ~OBJ_X_MASK) | (x & OBJ_X_MASK);
}

void set_object_id(OBJ_ATTRIBUTE* object, u32 ID)
{
	object->attrib2 = (object->attrib2 & ~OBJ_ID_MASK) | (ID & OBJ_ID_MASK);
}

void vsync() //Should be changed to use interrupts
{
    while(REG_VCOUNT >= 160);
    while(REG_VCOUNT < 160);
}

int main()
{
	//Copy data into VRAM & pallete ram
	memcpy(VRAM_BLOCK_4, emeraldTiles, emeraldTilesLen);
	memcpy(PAL_SPRITE, emeraldPal, emeraldPalLen);

	init_objects();

	REG_DISPCNT= BG_OBJ | OBJ_ENABLE_1D;

	//Set OAM data
	//Should become a function
	OBJ_ATTRIBUTE* object1 = &obj_buffer[0];
	object1->attrib0 = ATTRIB0_8BPP | ATTRIB0_TALL;
	object1->attrib1 = ATTRIB1_SIZE_16;
	set_object_id(object1, (0 * SPRITE_SIZE));
	set_object_position(object1, 20, 0);

	OBJ_ATTRIBUTE* object2 = &obj_buffer[1];
	object2->attrib0 = ATTRIB0_8BPP | ATTRIB0_TALL;
	object2->attrib1 = ATTRIB1_SIZE_16;
	set_object_id(object2, (1 * SPRITE_SIZE));
	set_object_position(object2, 50, 0);

	OBJ_ATTRIBUTE* object3 = &obj_buffer[2];
	object3->attrib0 = ATTRIB0_8BPP | ATTRIB0_TALL;
	object3->attrib1 = ATTRIB1_SIZE_16;
	set_object_id(object3, (2 * SPRITE_SIZE));
	set_object_position(object3, 80, 0);

	OBJ_ATTRIBUTE* object4 = &obj_buffer[3];
	object4->attrib0 = ATTRIB0_8BPP | ATTRIB0_TALL;
	object4->attrib1 = ATTRIB1_SIZE_16;	
	set_object_id(object4, (3 * SPRITE_SIZE));
	set_object_position(object4, 110, 0);

	OBJ_ATTRIBUTE* object5 = &obj_buffer[4];
	object5->attrib0 = ATTRIB0_8BPP | ATTRIB0_TALL;
	object5->attrib1 = ATTRIB1_SIZE_16;	
	set_object_id(object5, (4 * SPRITE_SIZE));
	set_object_position(object5, 140, 0);

	memcpy((OBJ_ATTRIBUTE*)MEM_OAM, &obj_buffer, (sizeof(OBJ_ATTRIBUTE) * 5));

	s32 x1 = 90, y1 = 60;
	u32 id = 0;
	u32 frame_count = 0;
	u32 sprite_id = 0;

	while(1)
	{
		vsync();
		key_poll();

		if(frame_count > 40)
		{
			frame_count = 0;
		}
		else if(frame_count > 30)
		{
			sprite_id = 2;
		}
		else if(frame_count > 20)
		{
			sprite_id = 0;
		}
		else if (frame_count > 10)
		{
			sprite_id = 1;
		}
		else
		{
			sprite_id = 0;
		}

		if(key_pressed(KEY_LEFT) || key_held(KEY_LEFT))
		{
			frame_count++;
			object1->attrib1 &= ~ATTRIB1_HFLIP;
			id = 3;
			x1 += -1;
		}
		else if(key_pressed(KEY_RIGHT) || key_held(KEY_RIGHT))
		{
			frame_count++;
			object1->attrib1 |= ATTRIB1_HFLIP;
			id = 3;
			x1 += 1;
		}

        if(key_pressed(KEY_UP) || key_held(KEY_UP))
        {
			frame_count++;
			id = 6;
			y1 += -1;
        }
        else if(key_pressed(KEY_DOWN) || key_held(KEY_DOWN))
        {
			frame_count++;
			id = 0;
			y1 += 1;
        }

		if(!is_any_key_pressed())
		{
			sprite_id = 0;
		}

		set_object_id(object1, ((id + sprite_id) * SPRITE_SIZE));
		set_object_position(object1, x1, y1);

		memcpy((OBJ_ATTRIBUTE*)MEM_OAM, &obj_buffer, (sizeof(OBJ_ATTRIBUTE) * 5));
	}

	return 0;
}