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

#endif //CORE_TYPE