#ifndef _LORA_H
#define _LORA_H

#include "bsp.h"
#include "ring_buf.h"

extern char tx_buf[32];  //向上位机发送的数据
extern char my_uid_str[25];    //本机地址
extern int ID;
 // 定义环形缓冲区
extern ringbuffer_t uart3_rb;

// 本地处理缓冲区（用于从环形缓冲区读取后处理）
extern uint8_t uart3_process_buffer[128];
// DMA接收缓冲区
extern uint8_t uart3_rx_buffer[128];

void task_key(void);
void uid_p(void); //发送设备ID
void uart3_rx_init(void);
void uart3_show(void);

void uid_temp(void);


#endif

