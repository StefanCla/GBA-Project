#include <string.h>			//For memcpy
#include "core/core.h"

#include "sprites/plane.h"

#include "tiles/star_night.h"
#include "tiles/city_one.h"
#include "tiles/city_two.h"
#include "tiles/city_three.h"

//grit tile options used
//-gB4 -m -mLs -mRtpf -ftc -pn16 -mp1

u16 key_current = 0, key_previous = 0;

const u32 PLANE_SPRITE_SIZE = 8;

//A tile is an 8x8 bitmap
const u32 TILE_SIZE = 8;
const u32 TILE_COUNT = 64;

static inline void vsync() //Should be changed to use interrupts
{
    while(REG_VCOUNT >= 160);
    while(REG_VCOUNT < 160);
}

int main()
{
	u32 tileset_offset = 0;
	u32 mapset_offset = (CHARBLOCK_SIZE * 2);
	u32 palset_offset = 16;

	//Copy background data into vram & palette ram
	//Due to the naming of the maps, this is currently set manually
	//Consider making a tool to gather all bitmap data and copy via loop instead
	memcpy((u32*)MEM_VRAM, star_nightTiles, star_nightTilesLen);					//Char block 0
	memcpy((u32*)(MEM_VRAM + mapset_offset), star_nightMap, star_nightMapLen);		//Screen block 16
	memcpy(PAL_BG, star_nightPal, star_nightPalLen);

	tileset_offset += star_nightTilesLen;
	mapset_offset += star_nightMapLen;

	memcpy((u32*)(MEM_VRAM + tileset_offset), city_oneTiles, city_oneTilesLen);		//Char block 0
	memcpy((u32*)(MEM_VRAM + mapset_offset), city_oneMap, city_oneMapLen);			//Screen block 18
	memcpy((PAL_BG + (palset_offset * 1)), city_onePal, city_onePalLen);

	tileset_offset += city_oneTilesLen;
	mapset_offset += city_oneMapLen;

	memcpy((u32*)(MEM_VRAM + tileset_offset), city_twoTiles, city_twoTilesLen);		//Char block 0
	memcpy((u32*)(MEM_VRAM + mapset_offset), city_twoMap, city_twoMapLen);			//Screen block 20
	memcpy((PAL_BG + (palset_offset * 2)), city_twoPal, city_twoPalLen);

	tileset_offset += city_twoTilesLen;
	mapset_offset += city_twoMapLen;

	memcpy((u32*)(MEM_VRAM + tileset_offset), city_threeTiles, city_threeTilesLen);	//Char block 0
	memcpy((u32*)(MEM_VRAM + mapset_offset), city_threeMap, city_threeMapLen);		//Screen block 22
	memcpy((PAL_BG + (palset_offset * 3)), city_threePal, city_threePalLen);

	//Sprite data
	memcpy(VRAM_BLOCK_4, planeTiles, planeTilesLen);
	memcpy(PAL_SPRITE, planePal, planePalLen);

	REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(16) | BG_REG_SIZE_64x32 | BG_PRIORITY(3);
	REG_BG1CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(18) | BG_REG_SIZE_64x32 | BG_PRIORITY(2);
	REG_BG2CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(20) | BG_REG_SIZE_64x32 | BG_PRIORITY(1);
	REG_BG3CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(22) | BG_REG_SIZE_64x32 | BG_PRIORITY(0);

	init_objects();

	REG_DISPCNT= VMODE_0 | BG_0 | BG_1 | BG_2 | BG_3 | BG_OBJ | OBJ_ENABLE_1D;

	set_object_attributes(&obj_buffer[0],
		ATTRIB0_WIDE,
		ATTRIB1_SIZE_16,
		0);

	set_object_id(&obj_buffer[0], 0);
	set_object_position(&obj_buffer[0], 20, 60);

	memcpy((OBJ_ATTRIBUTE*)MEM_OAM, &obj_buffer, (sizeof(OBJ_ATTRIBUTE) * 1));

	u32 sprite_id = 0;
	s32 sprite_x = 20, sprite_y = 60;
	
	u32 bg_x = 0, bg_y = 0;
	u32 bg_x_1 = 0, bg_y_1 = 0;
	u32 bg_x_2 = 0, bg_y_2 = 0;
	u32 bg_x_3 = 0, bg_y_3 = 0;

	u32 frame_count = 0;

	OBJ_ATTRIBUTE* plane = &obj_buffer[0];

	while(1)
	{
		vsync();
		key_poll();

		frame_count++;

		if(key_pressed(KEY_UP) || key_held(KEY_UP))
		{
			sprite_id = 2;
			sprite_y += -1;
		}
		else if(key_pressed(KEY_DOWN) || key_held(KEY_DOWN))
		{
			sprite_id = 1;
			sprite_y += 1;
		}

		if(!is_any_key_pressed())
		{
			sprite_id = 0;
		}

		if(sprite_y < 0)
		{
			sprite_y = 0;
		}
		else if(sprite_y > 144)
		{
			sprite_y = 144;
		}

		set_object_id(plane, (sprite_id * PLANE_SPRITE_SIZE));
		set_object_position(plane, sprite_x, sprite_y);

		bg_x += 1;
		bg_x_1 += 2;
		bg_x_2 += 1;

		if(frame_count > 1)
		{
			bg_x_3 += 1;
			frame_count = 0;
		}

		REG_BG0HOFS = bg_x;
		REG_BG1HOFS = bg_x_1;
		REG_BG2HOFS = bg_x_2;
		REG_BG3HOFS = bg_x_3;

		memcpy((OBJ_ATTRIBUTE*)MEM_OAM, &obj_buffer, (sizeof(OBJ_ATTRIBUTE) * 1));
	}

	return 0;
}