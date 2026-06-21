#include "light.h"


uint8_t illuminance = 1; //光照等级
volatile uint32_t adc_light_buffer = 0;


// 光敏
void light_adc_data(void)
{
    uint32_t light_sum = 0;

    for(int i = 1; i < (30 * 2); i += 2)
    {
        light_sum += adc_buff[i];
    }
    adc_light_buffer = light_sum / 30;
		
		if(adc_light_buffer >= 3500) illuminance = 0;
		else if(adc_light_buffer >= 2000) illuminance = 1;
		else illuminance = 2;
		
		OLED_ShowString(4,1,"l:");
		OLED_ShowNum(4,3,illuminance,1);
}



