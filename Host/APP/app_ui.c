#include "app_ui.h"

void lcd_show(void)
{
		char temp[10];
	  static uint8_t lcd_1_init = 0;
    static uint8_t lcd_i = 0;
    if(!total_user_count){
        OLED_ShowString(1, 1, "   users not");
    }
    else{
        key_show();
        if(key_where == KEY1_SHOW)
        {
            lcd_i = (lcd_i + 1) % (total_user_count + 1);
        }
				
				//主界面，连接设备数目
        if(lcd_i == 0)
        {
					if(lcd_1_init == 0) OLED_Clear();
          lcd_1_init = 1;
					
					OLED_ShowString(1, 1, "Allocated IP:");
          OLED_ShowNum(2,1,total_user_count,3); 
					OLED_ShowString(3, 1, "                    ");
					OLED_ShowString(4, 1, "                    ");

        }
				
				//设备具体数值
				else 
				{
					if(lcd_1_init == 1) OLED_Clear();
					lcd_1_init = 0;
					
					//id号
					uint8_t dev_index = lcd_i - 1;   
					OLED_ShowString(1, 1, "ID  :");
          OLED_ShowNum(1, 4, dev_arr[dev_index].id, 4); 
					//温湿度
          OLED_ShowString(2, 1, "t :");
          OLED_ShowNum(2, 4, dev_arr[dev_index].id_temp, 2); 
          OLED_ShowString(2, 7, "h:");
          OLED_ShowNum(2, 9, dev_arr[dev_index].id_humi, 2); 
					//烟雾
          OLED_ShowString(3, 1, "mq:");
					sprintf(temp,"%2.1f",dev_arr[dev_index].id_ppm);
          OLED_ShowString(3, 4, temp);
					
					//光照等级
          OLED_ShowString(4, 1, "l:");
          OLED_ShowNum(4, 3, dev_arr[dev_index].id_light, 2);
					
					//人数
          OLED_ShowString(4, 7, "pol:");
          OLED_ShowNum(4, 9, dev_arr[dev_index].id_people, 2);
				}
    }
}

void test(void)
{
	static uint16_t i = 0;
	
	key_show();
	if(key_where == KEY1_SHOW){i ++;}
	char i_test[20];
	sprintf(i_test,"test:%d", i);
	OLED_ShowString(2, 1, i_test);
}



