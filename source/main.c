#include <string.h>
#include "core/core.h"
#include "sprites/emerald.h"
#include "sprites/metroid.h"

#include "tiles/star_night.h"
#include "tiles/city_one.h"
#include "tiles/city_two.h"
#include "tiles/city_three.h"

//grit tile options used
//-gB4 -m -mLs -mRtpf -ftc -pn16 -mp1

u16 key_current = 0, key_previous = 0;

const u32 EMERALD_SPRITE_SIZE = (8 * 2);	//8 tiles x 2 because of 8bpp
const u32 METROID_SPRITE_SIZE = (64 * 2);	//64 tiles x 2 because of 8bpp

const u32 EMERALD_SPRITE_COUNT = 9;
const u32 METROID_SPRITE_COUNT = 2;

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
	memcpy((u32*)MEM_VRAM, star_nightTiles, star_nightTilesLen);						//Char block 0
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

	//Copy sprite data into vram & palette ram
	memcpy(VRAM_BLOCK_4, emeraldTiles, emeraldTilesLen);
	memcpy(VRAM_BLOCK_4 + ((EMERALD_SPRITE_SIZE * EMERALD_SPRITE_COUNT) * TILE_SIZE), metroidTiles, metroidTilesLen);
	memcpy(PAL_SPRITE, emeraldPal, emeraldPalLen);

	REG_BG0CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(16) | BG_REG_SIZE_64x32 | BG_PRIORITY(3);
	REG_BG1CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(18) | BG_REG_SIZE_64x32 | BG_PRIORITY(2);
	REG_BG2CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(20) | BG_REG_SIZE_64x32 | BG_PRIORITY(1);
	REG_BG3CNT = BG_CHARBLOCK(0) | BG_SCREENBLOCK(22) | BG_REG_SIZE_64x32 | BG_PRIORITY(0);

	init_objects();

	REG_DISPCNT= VMODE_0 | BG_0 | BG_1 | BG_2 | BG_3 | BG_OBJ | OBJ_ENABLE_1D;

	//Set OAM data
	//Setting 5 objects for now
	const u32 OBJ_COUNT = 5;
	for(u32 i = 0; i < OBJ_COUNT; ++i)
	{
		set_object_attributes(&obj_buffer[i], 
			ATTRIB0_8BPP | ATTRIB0_TALL,
			ATTRIB1_SIZE_16,
			0);
		
		set_object_id(&obj_buffer[i], (i * EMERALD_SPRITE_SIZE));

		const u32 X_OFFSET = 30;
		set_object_position(&obj_buffer[i], (20 + (X_OFFSET * i)), 0);
	}

	const u32 EMERALD_TILE_COUNT = EMERALD_SPRITE_SIZE * EMERALD_SPRITE_COUNT;

	const u32 OBJ_COUNT_METROID = 2;
	for(u32 i = 0; i < OBJ_COUNT_METROID; ++i)
	{
		set_object_attributes(&obj_buffer[OBJ_COUNT + i], 
			ATTRIB0_8BPP,
			ATTRIB1_SIZE_64,
			0);
		
		set_object_id(&obj_buffer[OBJ_COUNT + i], (EMERALD_TILE_COUNT + (i * METROID_SPRITE_SIZE)));

		const u32 X_OFFSET = 64;
		set_object_position(&obj_buffer[OBJ_COUNT + i], (20 + (X_OFFSET * i)), 70);
	}

	memcpy((OBJ_ATTRIBUTE*)MEM_OAM, &obj_buffer, (sizeof(OBJ_ATTRIBUTE) * (OBJ_COUNT + OBJ_COUNT_METROID)));

	s32 x1 = 90, y1 = 60;
	u32 id = 0;
	u32 frame_count = 0;
	u32 sprite_id = 0;

	u32 bg_x = 0, bg_y = 0;
	u32 bg_x_1 = 0, bg_y_1 = 0;
	u32 bg_x_2 = 0, bg_y_2 = 0;
	u32 bg_x_3 = 0, bg_y_3 = 0;

	OBJ_ATTRIBUTE* object1 = &obj_buffer[0];

	set_object_position(object1, x1, y1);

	while(1)
	{
		vsync();
		key_poll();

		//Play animation
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
			object1->attrib1 &= ~ATTRIB1_HFLIP;
			id = 3;
			x1 += -1;

			bg_x -= 4;
			bg_x_1 -= 3;
			bg_x_2 -= 2;
			bg_x_3 -= 1;
		}
		else if(key_pressed(KEY_RIGHT) || key_held(KEY_RIGHT))
		{
			object1->attrib1 |= ATTRIB1_HFLIP;
			id = 3;
			x1 += 1;

			bg_x += 4;
			bg_x_1 += 3;
			bg_x_2 += 2;
			bg_x_3 += 1;
		}

		if(key_pressed(KEY_UP) || key_held(KEY_UP))
		{
			id = 6;
			y1 += -1;
		}
		else if(key_pressed(KEY_DOWN) || key_held(KEY_DOWN))
		{
			id = 0;
			y1 += 1;
		}

		if(!is_any_key_pressed())
		{
			sprite_id = 0;
			frame_count = 0;
		}
		else
		{
			frame_count++;
		}

		set_object_id(object1, ((id + sprite_id) * EMERALD_SPRITE_SIZE));
		//set_object_position(object1, x1, y1);

		REG_BG0HOFS = bg_x;
		REG_BG1HOFS = bg_x_1;
		REG_BG2HOFS = bg_x_2;
		REG_BG3HOFS = bg_x_3;

		memcpy((OBJ_ATTRIBUTE*)MEM_OAM, &obj_buffer, (sizeof(OBJ_ATTRIBUTE) * (OBJ_COUNT + OBJ_COUNT_METROID)));
	}

	return 0;
}