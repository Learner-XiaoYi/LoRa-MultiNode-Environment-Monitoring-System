#ifndef _BSP_TIM_H
#define _BSP_TIM_H

#include "bsp.h"

void tim2_init(void);
void tim_delay_init(void);
void tim_delay_us(uint16_t us);

void tim_delay_ms(uint32_t ms);

#endif
