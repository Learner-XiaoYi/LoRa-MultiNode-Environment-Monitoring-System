#include "ring_buf.h"

void ringbuffer_init(ringbuffer_t *rb) 	
{
    rb->r = 0;
    rb->w = 0;
    memset(rb->buffer, 0, sizeof(uint8_t) * RINGBUFFER_SIZE);
    rb->itemCount = 0;
}

// 检查环形缓冲区是否已满
uint8_t ringbuffer_is_full(ringbuffer_t *rb) 
{
    return (rb->itemCount == RINGBUFFER_SIZE);
}

// 检查环形缓冲区是否为空
uint8_t ringbuffer_is_empty(ringbuffer_t *rb) 
{
    return (rb->itemCount == 0);
}

// 向环形缓冲区写入数据
int8_t ringbuffer_write(ringbuffer_t *rb, uint8_t *data, uint32_t num) 
{
    // 如果要写入的数据量大于缓冲区剩余空间，返回错误
    if (num > (RINGBUFFER_SIZE - rb->itemCount)) 	
		{
        return -1;
    }
    
    // 写入数据
    while (num--) 	
		{
        rb->buffer[rb->w] = *data++;
        rb->w = (rb->w + 1) % RINGBUFFER_SIZE;
        rb->itemCount++;
    }
    
    return 0;  // 写入成功
}

// 从环形缓冲区读取数据
int8_t ringbuffer_read(ringbuffer_t *rb, uint8_t *data, uint32_t num) 
{
    // 如果要读取的数据量大于缓冲区中的数据量，返回错误
    if (num > rb->itemCount) 	
		{
        return -1;
    }
    
    // 读取数据
    while (num--) 	
		{
        *data++ = rb->buffer[rb->r];
        rb->r = (rb->r + 1) % RINGBUFFER_SIZE;
        rb->itemCount--;
    }
    
    return 0;  // 读取成功
}

// 获取可读数据量
uint32_t ringbuffer_available(ringbuffer_t *rb) 
{
    return rb->itemCount;
}

