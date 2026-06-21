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
	{read_dh11_data,50,0},
	{mq_adc_data,200,0},
	{light_adc_data,200,0},
	{uart1_show,500,0},
	{uart3_show,500,0},
	{task_key,1000,0}
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
	tim_delay_init();
	OLED_Init();
	mq135_init();
	uart1_rx_init();
	uart3_rx_init();
	
	
//	test_function();
}	
