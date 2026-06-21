#include "Lora.h"

//串口3

char tx_buf[32] = {0};  //向上位机发送的数据

char my_uid_str[25];    //本机地址

//发送
void uid_temp(void)
{
	uart3_printf("%s", tx_buf);
}

//获取并发送地址
void uid_p(void)
{
    volatile uint32_t uid0 = HAL_GetUIDw0(); 
    volatile uint32_t uid1 = HAL_GetUIDw1();
    volatile uint32_t uid2 = HAL_GetUIDw2();

		sprintf(tx_buf, "UID:%08X%08X%08X\r\n", uid0, uid1, uid2);
		sprintf(my_uid_str, "%08lX%08lX%08lX", uid0, uid1, uid2);
		uart3_printf("%s", tx_buf);
}

int ID = -1;

// 1. 定义缓冲区
char data_buf[64] = {0};

void task_key(void)
{
	static uint8_t i = 0;
	if(ID == -1)
	{
		i = 0;
		OLED_ShowString(1,1,"ID:NO deal!");
		uid_p();
	}
	else
	{
		if(!i)
		{
			OLED_ShowString(1,1,"                    ");
			i = 1;
		}
		char ID_show[20] = {0};
    sprintf(ID_show,"ID:%04hhu",ID);
		OLED_ShowString(1, 1, ID_show);
		//发送格式:   id:0001;temp:27,humi:40,ppm:130.8,light:1,people:00
		sprintf(data_buf, "temp:%02hhu,humi:%02hhu,ppm:%.1f,light:%01hhu,people:%02hu", temp, humi, ppm, illuminance, people_data);
		uart3_printf("id:%04d;%s\r\n",ID,data_buf);
	}
}


/*------------------------------------接收数据----------------------------------------------*/
// 定义环形缓冲区
ringbuffer_t uart3_rb;

// 本地处理缓冲区（用于从环形缓冲区读取后处理）
uint8_t uart3_process_buffer[128] = {0};

// DMA接收缓冲区
uint8_t uart3_rx_buffer[128] = {0};


void uart3_rx_init(void) 
{
	 // 初始化环形缓冲区
    ringbuffer_init(&uart3_rb);
		
	//空闲中断	
	HAL_UARTEx_ReceiveToIdle_DMA(&huart3,uart3_rx_buffer,sizeof(uart3_rx_buffer));

}

void uart3_show(void) 
{
	
    // 检查环形缓冲区是否有数据
    if (ringbuffer_is_empty(&uart3_rb)) 			
	{
			
        return;
    }
		
		// 获取可读数据量
    uint32_t available = ringbuffer_available(&uart3_rb);
	
		  // 确保不超过处理缓冲区大小
    uint32_t read_len = (available > sizeof(uart3_process_buffer)) ? sizeof(uart3_process_buffer) : available;
	
	if (ringbuffer_read(&uart3_rb, uart3_process_buffer, read_len) == 0) 	
	{
		
/*------------------------------格式： UID:066EFF505653884887223353;ID:0001-----------------------------*/
		uart3_process_buffer[read_len] = '\0'; // 添加字符串结束符
		
//		uart2_printf("DEBUG RAW: [%s]\r\n", uart2_process_buffer);
		
		/*接收ID号*/
		if(ID == -1)
		{
			char *UID_key = strstr((char*)uart3_process_buffer,"UID:");
			if(UID_key != NULL)
			{
				char *UID_key_str = UID_key + 4;
				if(strncmp(UID_key_str,my_uid_str,24) == 0)
				{
					char *ID_key = strstr(UID_key,"id:");
					ID = atoi(ID_key + 3);
				}
			}
		}
   }
}

