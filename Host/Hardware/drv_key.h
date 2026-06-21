#ifndef _DRV_KEY_H
#define _DRV_KEY_H

#include "bsp.h"

typedef enum
{
	KEY_NO,
	KEY1_SHOW,
	KEY2_SHOW,
	KEY3_SHOW,
	KEY1_LONG,
	KEY2_LONG,
	KEY3_LONG
}KEY_WHERE;

extern KEY_WHERE key_where;

typedef enum
{
	KEY_init,
	KEY_watt_down,
	KEY_down,
	KEY_long_down_D,
	KEY_long_down
}KEY_STATE;

extern uint16_t key_tick;

void key_show(void);



#endif
