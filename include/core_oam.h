//OAM defines

#ifndef CORE_OAM
#define CORE_OAM

#define OBJ_X_MASK          0x01FF
#define OBJ_Y_MASK          0x00FF
#define OBJ_ID_MASK         0x01FF

//Attribute defines
//Attribute 0
#define ATTRIB0_HIDE        0x0200
#define ATTRIB0_TALL		0x8000
#define ATTRIB0_8BPP        0x2000

//Attribute 1
#define ATTRIB1_SIZE_64     0xC000
#define ATTRIB1_SIZE_16   	0x8000
#define ATTRIB1_HFLIP       0x1000
#define ATTRIB1_VFLIP       0x2000

#endif //CORE_OAM