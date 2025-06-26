//OAM defines

#ifndef CORE_OAM
#define CORE_OAM

#include "core_type.h"

#define OBJ_X_MASK          0x01FF
#define OBJ_Y_MASK          0x00FF
#define OBJ_ID_MASK         0x01FF

//Attribute defines
//Attribute 0
#define ATTRIB0_HIDE        0x0200
#define ATTRIB0_TALL		0x8000
#define ATTRIB0_WIDE        0x4000
#define ATTRIB0_8BPP        0x2000

//Attribute 1
#define ATTRIB1_SIZE_64     0xC000
#define ATTRIB1_SIZE_16   	0x8000
#define ATTRIB1_HFLIP       0x1000
#define ATTRIB1_VFLIP       0x2000

//Extern
extern const u32 MAX_OBJECT_REG;
extern OBJ_ATTRIBUTE obj_buffer[128];

//Functions declarations
void init_objects();

//Inline
static inline void set_object_attributes(OBJ_ATTRIBUTE* obj, u16 a0, u16 a1, u16 a2)
{
    obj->attrib0 = a0, obj->attrib1 = a1, obj->attrib2 = a2;
}

static inline void set_object_position(OBJ_ATTRIBUTE* obj, u32 x, u32 y)
{
    //We zero-out the first 8 bits of attribute 0, and set the first 8 bits of Y into the attribute
	obj->attrib0 = (obj->attrib0 & ~OBJ_Y_MASK) | (y & OBJ_Y_MASK);

	//Same but with 9 bits & X value
	obj->attrib1 = (obj->attrib1 & ~OBJ_X_MASK) | (x & OBJ_X_MASK);
}

static inline void set_object_id(OBJ_ATTRIBUTE* obj, u32 id)
{
    obj->attrib2 = (obj->attrib2 & ~OBJ_ID_MASK) | (id & OBJ_ID_MASK);
}

#endif //CORE_OAM