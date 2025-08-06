#include "core/core.h"

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

extern BACKGROUND_DATA* current_backgrounds[4]; //Will have max 4 backgrounds running

extern u32 tileset_offset;
extern u32 mapset_offset;
extern const u16 palset_offset;
extern u32 current_background_count;

BACKGROUND_DATA* new_background_data();
bool load_background(BACKGROUND_DATA* background);
bool clear_background(BACKGROUND_DATA** background);
void setup_backgrounds();

// clear all backgrounds();
// load specific backgrounds?
