#ifndef __DH11_H
#define __DH11_H

#include "bsp.h"

//DHT11引脚宏定义
#define DHT11_GPIO_PORT  GPIOA
#define DHT11_GPIO_PIN   GPIO_PIN_5
//#define DHT11_GPIO_CLK   RCC_APB2Periph_GPIOA
/*********************END**********************/
 
//输出状态定义
#define OUT 1
#define IN  0

extern u8 temp;
extern u8 humi;
 
//控制DHT11引脚输出高低电平
#define DHT11_Low  HAL_GPIO_WritePin(DHT11_GPIO_PORT,DHT11_GPIO_PIN,GPIO_PIN_RESET)
#define DHT11_High HAL_GPIO_WritePin(DHT11_GPIO_PORT,DHT11_GPIO_PIN,GPIO_PIN_SET)

u8 DHT11_Init(void);//初始化DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//读取温湿度数据
u8 DHT11_Read_Byte(void);//读取一个字节的数据
u8 DHT11_Read_Bit(void);//读取一位的数据
void DHT11_Mode(u8 mode);//DHT11引脚输出模式控制
u8 DHT11_Check(void);//检测DHT11
void DHT11_Rst(void);//复位DHT11   

void read_dh11_data(void);

#endif
