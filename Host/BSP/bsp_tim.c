#include "bsp_tim.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static uint16_t ack_tm = 0; 
	if(htim -> Instance == TIM2)
	{
		key_tick ++; //°´¼ü¼ÆÊý
		ack_tm ++;
		if(ack_tm >= 3000)  
		{
			ack_flg = 1;
			ack_tm = 0;
		}
	}
}

void tim2_init(void)
{
		HAL_TIM_Base_Start_IT(&htim2);
}

void tim_delay_init(void)
{
   HAL_TIM_Base_Start(&htim6);
	TIM6->CNT = 0; 
    
}

void tim_delay_us(uint16_t us)
{
    uint16_t start = TIM6->CNT;
    while((uint16_t)(TIM6->CNT - start) < us);
		
}

void tim_delay_ms(uint32_t ms)
{
    while(ms--)
    {
        tim_delay_us(1000);
    }
}


