#include "map_setup.h"
#include <stdlib.h>

#include "tiles/star_night.h"
#include "tiles/city_one.h"
#include "tiles/city_two.h"
#include "tiles/city_three.h"

//Most of the below var's should be on EWRAM, as we carely access them on runtime, only in level transitions.
BACKGROUND_DATA* current_backgrounds[4];

u32 tileset_offset = 0;
u32 mapset_offset = (CHARBLOCK_SIZE * 2);
const u16 palset_offset = 16;
u32 current_background_count = 0;

// I dont like that we use index to know which one we set
// Explore the possibility of malloc here
// And passed that into load_backgrounds
BACKGROUND_DATA* new_background_data(
	const u32* tile_data, u32 tile_len,
	const u16* map_data, u32 map_len,
	const u16* pal_data, u32 pal_len,
	const u32 index)
{
    BACKGROUND_DATA* new_background = malloc(sizeof(BACKGROUND_DATA)); //Should be allocated on EWRAM

	new_background->tile_data = tile_data;
	new_background->tile_len = tile_len;

	new_background->map_data = map_data;
	new_background->map_len = map_len;

	new_background->pal_data = pal_data;
	new_background->pal_len = pal_len;

	new_background->index = index;

    current_backgrounds[index] = new_background;

	return new_background;
}

bool load_background(BACKGROUND_DATA* background)
{
    if(!background)
    {
        return false;
    }

    if(current_background_count > 3)
    {
        //I dont think I can provide logging (unless I use mGBA for logging perhaps)
        //Clear one or more backgrounds to set a new one.
        return false;
    }

    memcpy((u32*)(MEM_VRAM + tileset_offset), background->tile_data, background->tile_len);
    memcpy((u32*)(MEM_VRAM + mapset_offset), background->map_data, background->map_len);
    memcpy((u16*)(PAL_BG + (palset_offset * current_background_count)), background->pal_data, background->pal_len);

    current_background_count++;
    tileset_offset += background->tile_len;
    mapset_offset += background->map_len;

    return true;
}

bool clear_background(BACKGROUND_DATA** background)
{
    BACKGROUND_DATA* local_bg = *background;
    if(!*background)
    {
        return false;
    }

    u32 tile_startpoint = 0;
    u32 map_startpoint = (CHARBLOCK_SIZE * 2);
    u32 pal_startpoint = 0;

    for(u32 i = 0; i < local_bg->index; i++)
    {
        tile_startpoint += current_backgrounds[i]->tile_len;
        map_startpoint += current_backgrounds[i]->map_len;
        //pal_startpoint += current_backgrounds[i]->pal_len;
    }

    //what if 256 color pal?
    pal_startpoint = palset_offset * local_bg->index;

    memset((u32*)(MEM_VRAM + tile_startpoint), 0, local_bg->tile_len);
    memset((u32*)(MEM_VRAM + map_startpoint), 0, local_bg->map_len);
    memset((u16*)(PAL_BG + pal_startpoint), 0, local_bg->pal_len);

    current_backgrounds[local_bg->index] = NULL;
    free(*background);
    *background = NULL;
    return true;
}

void setup_backgrounds()
{
    BACKGROUND_DATA* background = NULL;

	background = new_background_data(
		&star_nightTiles, star_nightTilesLen,
		&star_nightMap, star_nightMapLen,
		&star_nightPal, star_nightPalLen,
		0
	);
    load_background(background);

	background = new_background_data(
		&city_oneTiles, city_oneTilesLen,
		&city_oneMap, city_oneMapLen,
		&city_onePal, city_onePalLen,
		1
	);
    load_background(background);

	background = new_background_data(
		&city_twoTiles, city_twoTilesLen,
		&city_twoMap, city_twoMapLen,
		&city_twoPal, city_twoPalLen,
		2
	);
    load_background(background);

	background = new_background_data(
		&city_threeTiles, city_threeTilesLen,
		&city_threeMap, city_threeMapLen,
		&city_threePal, city_threePalLen,
		3
	);
    load_background(background);
}