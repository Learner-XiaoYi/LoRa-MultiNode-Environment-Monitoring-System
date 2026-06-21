#include "LD6001.h"
#include "ring_buf.h" 

u8 people_data = 0;//人数

/*------------------------------------接收数据----------------------------------------------*/
// 定义环形缓冲区
ringbuffer_t uart1_rb;

// 本地处理缓冲区（用于从环形缓冲区读取后处理）
uint8_t uart1_process_buffer[128] = {0};

// DMA接收缓冲区
uint8_t uart1_rx_buffer[128] = {0};


void uart1_rx_init(void) 
{
	 // 初始化环形缓冲区
    ringbuffer_init(&uart1_rb);
		
	//空闲中断	
	HAL_UARTEx_ReceiveToIdle_DMA(&huart1,uart1_rx_buffer,sizeof(uart1_rx_buffer));

}

/*-----------------毫米波发送--------------*/
void send_ld_6001(void)
{	
	static uint8_t steat_1 = 0;
	if(!steat_1)
	{
		//查询模块状态信息 0x11
//		uart1_printf(RADAR_CMD_QUERY_STATUS);
		uint8_t cmd[] = "44110000554b";
    uart1_printf((const char *)cmd, sizeof(cmd));
		steat_1 = 1;
	}
	if(steat_1)
	{
		//获取雷达检测数据命令 0x62
//		uart1_printf(RADAR_CMD_GET_DETECT_DATA);
		uint8_t cmd[] = "446208001000000000000000BE4B";
    uart1_printf((const char *)cmd, sizeof(cmd));
	}
	
}


/*---------- 毫米波接收-----------*/
void uart1_show(void) 
{
		send_ld6001_by_your_logic();
		OLED_ShowString(4,9,"p:");
		OLED_ShowNum(4,11,people_data,2);
    // 检查环形缓冲区是否有数据
    if (ringbuffer_is_empty(&uart1_rb)) 			
		{
        return;
    }
		
		// 获取可读数据量
    uint32_t available = ringbuffer_available(&uart1_rb);
	
		  // 确保不超过处理缓冲区大小
    uint32_t read_len = (available > sizeof(uart1_process_buffer)) ? sizeof(uart1_process_buffer) : available;
	
	if (ringbuffer_read(&uart1_rb, uart1_process_buffer, read_len) == 0) 	
	{
			uart1_process_buffer[read_len] = '\0'; // 添加字符串结束符
		
/*-----------------------------------------业务逻辑 雷达启动----------------------------------------------*/
		char *radar_head = strstr((const char *)uart1_process_buffer, (char *)"\x4D\x62"); // 4D 62 是雷达数据帧头
		if(radar_head != NULL)
		{
			people_data = *(radar_head + 5); // 直接取人数
		}
   }
}

void send_ld6001_by_your_logic(void)
{
    uint8_t data[14] = {
        0x44, 0x62, 0x08, 0x00, 0x10, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0xBE, 0x4B
    };
    HAL_UART_Transmit(&huart1, data, 14, 100);
}








