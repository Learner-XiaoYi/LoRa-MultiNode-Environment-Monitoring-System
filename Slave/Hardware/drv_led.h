#ifndef _DRV_LED_H
#define _DRV_LED_H

#include "bsp.h"

typedef struct {
    GPIO_TypeDef *port;
    uint16_t pin;
} GPIO_IO_t;

typedef struct {
    GPIO_IO_t R;
    GPIO_IO_t G;
    GPIO_IO_t B;
} LED_RGB_t;

extern LED_RGB_t led1;

void LED_Set(LED_RGB_t *led, uint8_t r, uint8_t g, uint8_t b);
void LED_Toggle(LED_RGB_t *led);
#endif
