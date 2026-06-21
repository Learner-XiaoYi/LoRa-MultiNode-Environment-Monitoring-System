#ifndef _ME_UART_H
#define _ME_UART_H

#include "bsp.h"

/*
    URAT1
    PA10 -- USART_RX           PA9 -- USART_TX

*/

extern UART_HandleTypeDef huart1;  // 串口1
extern UART_HandleTypeDef huart3;  // 串口3



void uart1_printf(const char *format, ...);
void uart2_printf(const char *format, ...);
void uart3_printf(const char *format, ...);

//void simple1_test(void);
void test_function(void);
void simple2_test(void);


#endif
