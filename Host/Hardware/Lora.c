#include "Lora.h"

uint8_t temp; //温度
uint8_t humi; //湿度
uint16_t ppm;  //气体浓度
uint16_t people_data;    //人数


DeviceData_t dev_arr[MAX_DEVICE_COUNT];

uint16_t total_user_count = 0;//已分配用户数


//初始化从机设备
void DevArr_Init(void)
{
    uint8_t i;
    for(i=0; i<MAX_DEVICE_COUNT; i++)
    {
        memset(dev_arr[i].id_buffer, 0, UID_STR_MAX_LEN);
        dev_arr[i].id = -1;
        // 初始化传感器数据为0
        dev_arr[i].id_temp = 0;
        dev_arr[i].id_humi = 0;
        dev_arr[i].id_ppm = 0.0;
				dev_arr[i].id_light = 0;
        dev_arr[i].id_people = 0;
    }
}



//向云平台发送 uart2
void task_key(void)
{
    char temp[128];
    static uint8_t send_idx = 0;   //前发到第几个设备
    
    if (total_user_count == 0) return;  // 无设备直接退出
    
    // 如果索引超出范围，从头开始循环
    if (send_idx >= total_user_count) {
        send_idx = 0;
    }
    
    // 发送当前索引对应的设备数据
    if (dev_arr[send_idx].id > 0) {
        sprintf(temp, "id:%04d,temp:%02hhu,humi:%02hhu,ppm:%.1f,light:%u,people:%02hu",
                dev_arr[send_idx].id, 
                dev_arr[send_idx].id_temp,
                dev_arr[send_idx].id_humi,
                dev_arr[send_idx].id_ppm,
                dev_arr[send_idx].id_light,
                dev_arr[send_idx].id_people);
        uart2_printf("%s", temp);
    }
    
    // 指向下一个设备，下次调用时发送
    send_idx++;
}


//向上位机发送 uart3
void task3_key(void)
{
    char temp[128];
    for (uint8_t i = 0; i < total_user_count; i++)
    {
        if(dev_arr[i].id > 0)
        {
            sprintf(temp,"id:%04d;temp:%02hhu,humi:%02hhu,ppm:%.1f,light:%u,people:%02hu\r\n",
                dev_arr[i].id, 
                dev_arr[i].id_temp,
                dev_arr[i].id_humi,
                dev_arr[i].id_ppm,
                dev_arr[i].id_light,
                dev_arr[i].id_people);
            uart3_printf("%s",temp);
        }
    } 
}

void tase_tpem(void)
{
//	static int i = 0;
//	i ++;
//	uart2_printf("%d",i);
//	uart2_printf("id:0096;temp:11,humi:05,adc:0015,people:06");
}

// 定义环形缓冲区
ringbuffer_t uart1_rb;

// 本地处理缓冲区
uint8_t uart1_process_buffer[128] = {0};

// DMA接收缓冲区
uint8_t uart1_rx_buffer[128] = {0};


void uart1_rx_init(void) 
{
	 // 初始化环形缓冲区
    ringbuffer_init(&uart1_rb);
		
		//扩展，空闲中断	
		HAL_UARTEx_ReceiveToIdle_DMA(&huart1,uart1_rx_buffer,sizeof(uart1_rx_buffer));

}

uint8_t IDR_IP[MAX_DEVICE_COUNT] = {0};  //设备IP总数，
uint16_t IDR_IP_index = 0;

//设备分配的ID号
void IDR_IP_init(void)
{
    for(int i = 0;i < MAX_DEVICE_COUNT;i ++)
    {
        IDR_IP[i] = i + 1;
    }
}

void uart1_show(void) 
{
    int dev_index = 0; //数组索引
    uint16_t id_test;   //接收来自从机的ID
    uint8_t temp_test = 0; //接收来自从机的温度
		uint8_t humi_test = 0;//接收来自从机的湿度
		float ppm = 0; //接收来自从机的烟雾
		uint8_t light_test = 0; //接收来自从机的光照等级
		uint16_t people_data_test = 0;//接收来自从机的人数

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
//        // 清屏
        OLED_Clear();
         // 显示数据
        uart1_process_buffer[read_len] = '\0'; // 添加字符串结束符
            
/*-------------------------主机ID分配----------------------------------------------*/
		
		//调试
        char id_buffer[56];
        char *IDR_temp = strstr((char *)uart1_process_buffer,"UID:");
        if(IDR_temp != NULL)
        {
            total_user_count ++;//分配用户+1/用于计数

            char UID_text[25] = {0};//临时存储纯UID
            strncpy(UID_text,IDR_temp+4,24);//截取UID
            strcpy(dev_arr[IDR_IP_index].id_buffer, UID_text);//存储UID
            dev_arr[IDR_IP_index].id = IDR_IP[IDR_IP_index];//存储分配ID
            sprintf(id_buffer,"UID:%s,id:%04d",dev_arr[IDR_IP_index].id_buffer,IDR_IP[IDR_IP_index]);
            IDR_IP_index ++;//分配用户号+1 /索引/用于ID加一
            uart1_printf("%s",id_buffer);
        }
/*-------------------------------id解析--------------------------------------------*/
            char *id_key = strstr((char *)uart1_process_buffer,"id:");
            if(id_key != NULL)
            {
                char *id_key_str = id_key + 3;
                id_test = atoi(id_key_str);

                dev_index = id_test - 1;//计算设备索引
							  if (dev_index >= 0 && dev_index < total_user_count)
								{
									dev_arr[dev_index].id = id_test; //存储id
									
									
									/*---------------------temp温度处理解析--------------------------------------------*/
									char *temp_key = strstr((char *)uart1_process_buffer,"temp:");
									if(temp_key != NULL)
									{
											char *temp_key_str = temp_key + 5;
											temp_test = atoi(temp_key_str);
											dev_arr[dev_index].id_temp = temp_test; //存储温度
			//                char temp_show_buf[16] = {0};
			//                sprintf(temp_show_buf,"T:%02hhu",temp_test);
			//                OLED_ShowString(2, 1, temp_show_buf);
									}

			/*-------------------humi_test湿度----------------------------*/						
									char *humi_key = strstr((char *)uart1_process_buffer,"humi:");
									if(humi_key != NULL)
									{
											char *humi_key_str = humi_key + 5;
											humi_test = atoi(humi_key_str);
											dev_arr[dev_index].id_humi = humi_test; //存储湿度id_adc_mq
			//                char humi_show_buf[16] = {0};
			//                sprintf(humi_show_buf,"H:%02hhu",humi_test);
			//                OLED_ShowString(2, 7, humi_show_buf);
									}
			/*---------------------ppm:烟雾浓度----------------------*/
									char *adc_mq_buffer_test_key = strstr((char *)uart1_process_buffer,"ppm:");
									if(adc_mq_buffer_test_key != NULL)
									{
											char *adc_mq_buffer_test_key_str = adc_mq_buffer_test_key + 4;
											ppm = atof(adc_mq_buffer_test_key_str);
											dev_arr[dev_index].id_ppm = ppm; //存储id_adc_mqid_people
			//                char adc_mq_buffer_testbuf[16] = {0};
			//                sprintf(adc_mq_buffer_testbuf,"ADC:%04hu",adc_mq_buffer_test);
			//                OLED_ShowString(3, 1, adc_mq_buffer_testbuf);
									}
			/*----------------------------光照等级-------------------------------*/
									char *light_test_key = strstr((char *)uart1_process_buffer,"light:");
									if(light_test_key != NULL)
									{
											char *light_test_key_str = light_test_key + 6;
											light_test = (uint8_t )atoi(light_test_key_str);
											dev_arr[dev_index].id_light = light_test; //存储light_test

									}
			/*-----------------------people_data_test人数------------------------*/
									char *people_data_test_key = strstr((char *)uart1_process_buffer,"people:");
									if(people_data_test_key != NULL)
									{
											char *people_data_test_key_str = people_data_test_key + 7;
											people_data_test = atoi(people_data_test_key_str);
											dev_arr[dev_index].id_people = people_data_test; //存储id_people
			//                char adc_mq_buffer_test_show_buf[16] = {0};
			//                sprintf(adc_mq_buffer_test_show_buf,"Temp:%02hhu",people_data_test);
			//                OLED_ShowString(4, 1, adc_mq_buffer_test_show_buf);
									}

//                char id_show_buf[16] = {0};
//                sprintf(id_show_buf,"id:%04hhu",id_test);
//                OLED_ShowString(1, 1, id_show_buf);
									
									
								}else {return;}

                
            }

           
            
//				uart2_printf("buffer: %s\n", uart1_process_buffer);
//					OLED_ShowString(1, 1, (char *)uart1_process_buffer);
            
    //        // 清空处理缓冲区
            memset(uart1_process_buffer, 0, sizeof(uart1_process_buffer));
        }
}

