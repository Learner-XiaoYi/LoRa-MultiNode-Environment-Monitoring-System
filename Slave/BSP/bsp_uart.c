#include "bsp_uart.h"


void uart1_printf(const char *format, ...)
{
    char buffer[256];
    va_list args;
    
    va_start(args, format);
    int len = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    if (len > 0) 
    {
//			HAL_UART_Transmit(&huart1, (uint8_t *)buffer, len,100);
			
      HAL_UART_Transmit(&huart1, (uint8_t *)buffer, len, 100); 
			

    }
}

void uart3_printf(const char *format, ...)
{
    char buffer[256];
    va_list args;
    
    va_start(args, format);
    int len = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    if (len > 0) 
    {
			HAL_UART_Transmit(&huart3, (uint8_t *)buffer, len,100);
			
//      HAL_UART_Transmit_DMA(&huart3, (uint8_t *)buffer, len);
			

    }
}


/*串口2*/
uint16_t uart2_rx_index = 0;
uint32_t uart2_rx_ticks = 0;


void test_function(void)
{
    uart1_printf("你好 1\r\n");
	
    uart3_printf("你好 2\r\n");
}

//void simple1_test(void)
//{
////	TIM3_Delay_ms(100);
//    // 整数测试
//    uart1_printf("整数: %d\n", 12345);
//    
////		TIM3_Delay_ms(100);

//    // 浮点数测试  
//    uart1_printf("浮点数: %.3f\n", 3.14159);
//    	TIM3_Delay_ms(100);

//    // 英文测试
//    uart1_printf("英文: Hello World!\n");
//    	TIM3_Delay_ms(100);

//    // 中文测试
//    uart1_printf("中文: 测试成功！\n");
//    	TIM3_Delay_ms(100);

//    // 混合测试
//    uart1_printf("混合: ID=%d, 温度=%.1f°C, 状态=%s\n", 
//                1, 25.5, "正常");
//}

void simple2_test(void)
{

//	TIM3_Delay_ms(100);
//    uart2_printf("整数: %d\r\n", 12345);
//    TIM3_Delay_ms(100);
// 
//    uart2_printf("浮点数: %.3f\r\n", 3.14159);
//    
//	  TIM3_Delay_ms(100);


//    uart2_printf("英文: Hello World!\r\n");
//    
//	    TIM3_Delay_ms(100);


//    uart2_printf("中文: 测试成功！\r\n");

//    TIM3_Delay_ms(100);
//	

//    uart2_printf("混合: ID=%d, 温度=%.1f°C, 状态=%s\r\n", 
//                1, 25.5, "正常");
}


//#define USART_RX_LEN    14U 
////串口中断回调
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) 
//{
//    if (huart->Instance == USART1)
//    {

//        if (!ringbuffer_is_full(&uart1_rb))
//        {
//            ringbuffer_write(&uart1_rb, uart1_rx_buffer, USART_RX_LEN);
//        }

//        // 可选：清空接收缓冲区
//        memset(uart1_rx_buffer, 0, sizeof(uart1_rx_buffer));

//        HAL_UART_Receive_DMA(&huart1, uart1_rx_buffer, USART_RX_LEN);
//    }
////    if (huart->Instance == USART2) 
////    {
////        uart2_rx_ticks = uwTick;          // 更新最后接收时间
////        uart2_rx_index++;                         // 递增索引
////        
////        HAL_UART_Receive_IT(&huart2, &uart2_rx_buffer[uart2_rx_index], 1);
////    }
//}

//空闲中断
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	/*雷达*/
	  if (huart->Instance == USART1) 
    {
        // 检查环形缓冲区是否已满
        if (!ringbuffer_is_full(&uart1_rb)) 
        {
            // 将接收到的数据写入环形缓冲区
            ringbuffer_write(&uart1_rb, uart1_rx_buffer, Size);
        }
        else 
        {
            // 缓冲区已满，可以添加处理策略
        }
        
//        // 清空DMA接收缓冲区
//        memset(uart1_rx_buffer, 0, sizeof(uart1_rx_buffer));
        
        // 重新启动DMA接收
        HAL_UARTEx_ReceiveToIdle_DMA(&huart1, uart1_rx_buffer, sizeof(uart1_rx_buffer));
    }
	
//		/*LORA*/
    if (huart->Instance == USART3) 
    {
        // 检查环形缓冲区是否已满
        if (!ringbuffer_is_full(&uart3_rb)) 
        {
            // 将接收到的数据写入环形缓冲区
            ringbuffer_write(&uart3_rb, uart3_rx_buffer, Size);
        }
        else 
        {
            // 缓冲区已满，可以添加处理策略
        }
        
        // 清空DMA接收缓冲区
        memset(uart3_rx_buffer, 0, sizeof(uart3_rx_buffer));
        
        // 重新启动DMA接收
        HAL_UARTEx_ReceiveToIdle_DMA(&huart3, uart3_rx_buffer, sizeof(uart3_rx_buffer));
    }
}








