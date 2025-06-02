#include "core_oam.h"
#include "core_memdef.h"
#include <string.h>     //for memcpy

OBJ_ATTRIBUTE obj_buffer[128];
const u32 MAX_OBJECT_REG = sizeof(obj_buffer);

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