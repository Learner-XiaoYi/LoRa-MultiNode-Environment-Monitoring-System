#ifndef _BSP_H
#define _BSP_H

//HAL库
#include "main.h"

#include "gpio.h"
#include "tim.h"
#include "usart.h"

//C库
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>



//BSP层
#include "bsp_tim.h"
#include "bsp_uart.h"


typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;



//外部设备

#include "drv_led.h"
#include "drv_key.h"
#include "OLED.h"
#include "Lora.h"

//应用
#include "app_ui.h"

#include "scheduler.h"




#endif
