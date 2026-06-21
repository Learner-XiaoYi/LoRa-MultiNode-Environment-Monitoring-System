#include "bsp.h"

extern volatile uint16_t adc_buff[30 * 2];

extern volatile uint16_t adc_mq_buffer;
extern float ppm;

void mq135_init(void);
void mq_adc_data(void);


