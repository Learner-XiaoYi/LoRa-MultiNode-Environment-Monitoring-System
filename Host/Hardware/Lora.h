#ifndef _LORA_H
#define _LORA_H


#include "bsp.h"
#include "ring_buf.h"

/*----------------最大从机数*/
#define MAX_DEVICE_COUNT 128
// 设备物理地址（UID）字符串最大长度
#define UID_STR_MAX_LEN   32

typedef struct{
    char id_buffer[56]; //设备物理地址
    int id;    //设备ID
		uint8_t is_confirmed;    // 0=未确认，1=已收到ACK
    uint8_t id_temp; //接收来自从机的温度
		uint8_t id_humi;//接收来自从机的湿度
		float id_ppm;           // 气体浓度 (ppm)
		uint8_t id_light;       // 光照等级 (0~2)
		uint16_t id_people;//接收来自从机的人数
}DeviceData_t;

extern volatile uint8_t ack_flg;
extern uint16_t total_user_count;//已分配用户数
extern DeviceData_t dev_arr[MAX_DEVICE_COUNT];


extern ringbuffer_t uart1_rb;
extern uint8_t uart1_process_buffer[128];
extern uint8_t uart1_rx_buffer[128];


void task_key(void);//向上位机发送
void task3_key(void);//向云平台发送
void IDR_IP_init(void);

void uart1_rx_init(void);
void uart1_show(void);
void lcd_show(void);

void test(void);
void tase_tpem(void);


#endif

