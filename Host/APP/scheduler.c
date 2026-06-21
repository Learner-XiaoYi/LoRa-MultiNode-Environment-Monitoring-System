#include "scheduler.h"

uint32_t app_tick = 0;


typedef struct 
	{
		void (*task_func)(void);
		uint32_t rate_ms;
		uint32_t last_run;
  	}task_t;
	 
static task_t scheduler_task[] =
{
	{lcd_show,100,0},
	{task_key,2000,0},
	{task3_key,2000,0},
	{uart1_show,50,0}
};


uint8_t task_num;
void scheduler_init(void)
{
	task_num = sizeof(scheduler_task) / sizeof(task_t);
}

void scheduler_run(void) 
	{
		for(uint8_t i = 0;i < task_num;i++)
		{
			uint32_t now_time = uwTick; 
			if(now_time >= scheduler_task[i].rate_ms + scheduler_task[i].last_run)
			{
				scheduler_task[i].last_run = now_time;
				scheduler_task[i].task_func();
			}
		}
  }

void system_user_init(void)	
{
	
	scheduler_init();  //任务初始化
	tim2_init();
	tim_delay_init(); //延时
	uart1_rx_init();
	OLED_Init();  //OLED初始化
	IDR_IP_init();
	OLED_Clear();
}	
