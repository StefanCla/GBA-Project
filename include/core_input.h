// Input

#ifndef CORE_INPUT
#define CORE_INPUT

#include "core_memdef.h"

/* [REG_KEYINPUT] Input has 16 bit of space
*  +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
*  |  F  |  E  |  D  |  C  |  B  |  A  |  9  |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
*  |  -  |  -  |  -  |  -  |  -  |  -  |  L  |  R  |down | up  |left |right|start|selce|  B  |  A  |
*  +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
*
* Note: Bits are cleared when key is down, not set
*/

//Keys
#define KEY_A        0x0001
#define KEY_B        0x0002
#define KEY_SELECT   0x0004
#define KEY_START    0x0008
#define KEY_RIGHT    0x0010
#define KEY_LEFT     0x0020
#define KEY_UP       0x0040
#define KEY_DOWN     0x0080
#define KEY_R        0x0100
#define KEY_L        0x0200

#define KEY_MASK     0x03FF

extern u16 key_current, key_previous;

static inline void key_poll()
{
    key_previous = key_current;
    key_current = ~REG_KEYINPUT & KEY_MASK;
}

static inline u32 get_key_current()     { return key_current; }
static inline u32 get_key_previous()    { return key_previous; }
static inline u32 is_key_down(u32 key)  { return key_current & key; }
static inline u32 is_key_up(u32 key)    { return ~key_current & key; }
static inline u32 was_key_down(u32 key) { return key_previous & key; }
static inline u32 was_key_up(u32 key)   { return ~key_previous & key; }

static inline u32 key_held(u32 key)     { return (key_current & key_previous) & key; }  //Remaing the same
static inline u32 key_pressed(u32 key)  { return (key_current & ~key_previous) & key; } //Key is now pressed, was released before
static inline u32 key_released(u32 key) { return (~key_current & key_previous) & key; } //Key is now released, was pressed before

static inline u32 is_any_key_pressed()  { return (key_current & KEY_MASK); }

#endif //CORE_INPUT