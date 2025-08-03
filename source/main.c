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

//Should move map-loading stuff to their own respective file next time

//Not entirely sure if I like to store the lengths here
//As we effectively store it twice
//But for now, It allows us to loop
typedef struct
{
	u32 tile_len;
	u32 map_len;
	u32 pal_len; 
	u32 index;

	const u32* tile_data;
	const u16* map_data;
	const u16* pal_data;

} BACKGROUND_DATA;

BACKGROUND_DATA* backgrounds;

// I dont like that we use index to know which one we set
// Explore the possibility of malloc here
// And passed that into load_backgrounds
BACKGROUND_DATA* new_background_data(
	const u32* tile_data, u32 tile_len,
	const u16* map_data, u32 map_len,
	const u16* pal_data, u32 pal_len,
	const u32 index)
{
	backgrounds[index].tile_data = tile_data;
	backgrounds[index].tile_len = tile_len;

	backgrounds[index].map_data = map_data;
	backgrounds[index].map_len = map_len;

	backgrounds[index].pal_data = pal_data;
	backgrounds[index].pal_len = pal_len;

	backgrounds[index].index = index;

	return &backgrounds[index];
}

//We need to clear the backgrounds as well, perhaps this could be done via a similar function?
//Maybe we can pass an array in, either filled or empty, to clear the memory
void load_backgrounds(u32 total_backgrounds)
{
	u32 tileset_offset = 0;
	u32 mapset_offset = (CHARBLOCK_SIZE * 2);
	const u16 palset_offset = 16;	//Should not be hardcoded here, but for now we know its 16 always

	for(u32 i = 0; i < total_backgrounds; i++)
	{
		BACKGROUND_DATA* background = &backgrounds[i];

		memcpy((u32*)(MEM_VRAM + tileset_offset), background->tile_data, background->tile_len);
		memcpy((u32*)(MEM_VRAM + mapset_offset), background->map_data, background->map_len);
		memcpy((u16*)(PAL_BG + (palset_offset * i)), background->pal_data, background->pal_len);

		tileset_offset += background->tile_len;
		mapset_offset += background->map_len;
	}
}

void setup_backgrounds()
{
	backgrounds = malloc(4 * sizeof(BACKGROUND_DATA));

	new_background_data(
		&star_nightTiles, star_nightTilesLen,
		&star_nightMap, star_nightMapLen,
		&star_nightPal, star_nightPalLen,
		0
	);

	new_background_data(
		&city_oneTiles, city_oneTilesLen,
		&city_oneMap, city_oneMapLen,
		&city_onePal, city_onePalLen,
		1
	);

	new_background_data(
		&city_twoTiles, city_twoTilesLen,
		&city_twoMap, city_twoMapLen,
		&city_twoPal, city_twoPalLen,
		2
	);

	new_background_data(
		&city_threeTiles, city_threeTilesLen,
		&city_threeMap, city_threeMapLen,
		&city_threePal, city_threePalLen,
		3
	);

	load_backgrounds(4);
}

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
	setup_backgrounds();

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