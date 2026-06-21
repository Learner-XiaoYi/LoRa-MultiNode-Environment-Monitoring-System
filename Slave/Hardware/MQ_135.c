#include "MQ_135.h"

volatile uint16_t adc_buff[30 * 2] = {0};

void mq135_init(void)
{
    HAL_ADC_Start_DMA(&hadc1,(uint32_t *)adc_buff,30 * 2);
}

volatile uint16_t adc_mq_buffer = 0;

float ppm = 0;
void mq_adc_data(void)
{
    
		volatile uint16_t mq_bif = 0;
    for(int i = 0; i < (30 * 2);i += 2)
    {
        mq_bif += adc_buff[i];
    }
    adc_mq_buffer = mq_bif / 30;

		ppm = 98.0f * (adc_mq_buffer * 3.3f / 4095.0f) - 23.0f;
		if(ppm >= 65) LED_Toggle(&led1);
		else LED_Toggle(&led1);
		if(ppm < 0) ppm = 0; 
		char test[10] = {0};
		sprintf(test,"%2.1f",ppm);
    OLED_ShowString(3,1,"yw:");
    OLED_ShowString(3,4,test);
		OLED_ShowString(3,9,"ppm");
}


