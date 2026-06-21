#include "drv_led.h"

LED_RGB_t led1 = {
    {GPIOA, GPIO_PIN_0},  // R
    {GPIOA, GPIO_PIN_1},  // G
    {GPIOA, GPIO_PIN_2}   // B
};


//µÆÉ«
void LED_Set(LED_RGB_t *led, uint8_t r, uint8_t g, uint8_t b)
{
    HAL_GPIO_WritePin(led->R.port, led->R.pin, r ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(led->G.port, led->G.pin, g ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(led->B.port, led->B.pin, b ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

//ÁÁÃð
void LED_Toggle(LED_RGB_t *led)
{
    static uint8_t r = 0, g = 0, b = 0;
    r = !r;
    g = !g;
    b = !b;
    LED_Set(led, r, g, b);
}





