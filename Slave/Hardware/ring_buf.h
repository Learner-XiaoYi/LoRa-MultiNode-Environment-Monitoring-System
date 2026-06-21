#ifndef _RING_BUF_H
#define _RING_BUF_H

#include <stdint.h>  
#include <string.h>   

// 环形缓冲区大小
#define RINGBUFFER_SIZE 256

// 环形缓冲区结构体
typedef struct {
    uint32_t w;           // 写指针
    uint32_t r;           // 读指针
    uint8_t buffer[RINGBUFFER_SIZE];  // 数据缓冲区
    uint32_t itemCount;   // 当前数据项数
} ringbuffer_t;


// 函数声明
void ringbuffer_init(ringbuffer_t *rb);
uint8_t ringbuffer_is_full(ringbuffer_t *rb);
uint8_t ringbuffer_is_empty(ringbuffer_t *rb);
int8_t ringbuffer_write(ringbuffer_t *rb, uint8_t *data, uint32_t num);
int8_t ringbuffer_read(ringbuffer_t *rb, uint8_t *data, uint32_t num);
uint32_t ringbuffer_available(ringbuffer_t *rb);  // 获取可读数据量

#endif
