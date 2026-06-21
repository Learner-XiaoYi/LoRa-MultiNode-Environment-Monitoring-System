#ifndef _LD6001_H
#define _LD6001_H

#include "bsp.h"
#include "ring_buf.h"

// 雷达指令
#define RADAR_CMD_QUERY_STATUS    44110000554b
#define RADAR_CMD_GET_DETECT_DATA 446208001000000000000000BE4B

extern u8 people_data;
extern ringbuffer_t uart1_rb;
extern uint8_t uart1_process_buffer[128];
extern uint8_t uart1_rx_buffer[128];


void uart1_rx_init(void); 
void send_ld_6001(void);
void uart1_show(void); 
void send_ld6001_by_your_logic(void);

#endif
