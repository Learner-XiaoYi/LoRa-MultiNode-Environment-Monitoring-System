#include "drv_key.h"


uint8_t key_read(void)
{
	uint8_t text = 0;

	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0) == RESET){text = 1;}
	
	return text;
}


KEY_WHERE key_where = KEY_NO;
KEY_STATE key_state = KEY_init;
uint16_t key_tick;

void key_show(void)
{
    static uint32_t key_tick_last = 0; 
    uint8_t id = key_read();
    
    // 按键释放检测
    if(id == 0)
    {
        key_where = KEY_NO;
        if(uwTick - key_tick_last >= 20)  // 消抖20ms
        {
            key_state = KEY_watt_down;
            key_tick = 0;
        }
    }
    key_tick_last = uwTick;
    
    switch(key_state)
    {
        case KEY_init:
        case KEY_watt_down:
        {
            if(id != 0)
            {
                key_state = KEY_down;
                key_tick = 0;
            }
            break;
        }
        
        case KEY_down:
        {
            if(key_tick >= 20)  // 消抖20ms
            {
                if(id != 0)
                {
                    if(id == 1) key_where = KEY1_SHOW;
                    else if(id == 2) key_where = KEY2_SHOW;
                    else if(id == 3) key_where = KEY3_SHOW;
                    
                    key_state = KEY_long_down_D;
                    key_tick = 0;
                }
                else
                {
                    key_state = KEY_watt_down;
                    key_tick = 0;
                }
            }
            break;
        }
        
        case KEY_long_down_D:
        {
            if(key_tick >= 1000) 
            {
                if(id != 0)
                {
                    // 产生长按事件
                    if(id == 1) key_where = KEY1_LONG;
                    else if(id == 2) key_where = KEY2_LONG;
                    else if(id == 3) key_where = KEY3_LONG;
                    
                    key_state = KEY_long_down;
                    key_tick = 0;
                }
                else
                {
                    key_state = KEY_watt_down;
                    key_tick = 0;
                }
            }
            else if(id == 0)  // 提前释放
            {
                key_state = KEY_watt_down;
                key_tick = 0;
            }
            break;
        }
        
        case KEY_long_down:
        {
            if(id == 0)  // 释放
            {
                key_state = KEY_watt_down;
                key_tick = 0;
            }
            break;
        }
    }
}

