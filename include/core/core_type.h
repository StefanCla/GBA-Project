// Typedefines

#ifndef CORE_TYPE
#define CORE_TYPE

//Unsigned
typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
typedef unsigned long long  u64;

//Signed
typedef signed char         s8;
typedef signed short        s16;
typedef signed int          s32;
typedef signed long long    s64;

//Volatile Unsigned
typedef volatile u8     vu8;
typedef volatile u16    vu16;
typedef volatile u32    vu32;
typedef volatile u64    vu64;

//Volatile Signed
typedef volatile s8     vs8;
typedef volatile s16    vs16;
typedef volatile s32    vs32;
typedef volatile s64    vs64;

//Bool
#ifndef __cplusplus
typedef enum { false, true } bool;
#endif

//Section placement
#define EWRAM_DATA  __attribute__((section(".ewram")))
#define IWRAM_DATA  __attribute__((section(".iwram")))
#define EWRAM_BSS   __attribute__((section(".sbss")))

#define EWRAM_CODE  __attribute__((section(".ewram"), long_call))
#define IWRAM_CODE  __attribute__((section(".iwram"), long_call))

//Data alignment
#define ALIGN(n)    __attribute__((aligned(n)))
#define PACKED      __attribute__((packed))

//Object datatype
typedef struct OBJ_ATTRIBUTE
{
    u16 attrib0;
    u16 attrib1;
    u16 attrib2;
    s16 filler;
} ALIGN(4) OBJ_ATTRIBUTE;

//Affine object data type
//Note: 4 regular objects fit in 1 affine object
typedef struct OBJ_AFFINE
{
    u16 filler0[3];
    s16 pa;
    u16 filler1[3];
    s16 pb;
    u16 filler2[3];
    s16 pc;
    u16 filler3[3];
    s16 pd;
} ALIGN(4) OBJ_AFFINE;

#endif //CORE_TYPE