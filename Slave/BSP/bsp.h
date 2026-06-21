#ifndef _BSP_H
#define _BSP_H

//HAL库
#include "main.h"




#include "gpio.h"
#include "tim.h"
#include "adc.h"
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
#include "OLED.h"
#include "DH11.h"
#include "MQ_135.h"
#include "light.h"
#include "LD6001.h"
#include "Lora.h"

//应用
#include "scheduler.h"



#endif
