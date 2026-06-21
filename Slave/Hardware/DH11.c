#include "DH11.h"

         
     
//复位DHT11
void DHT11_Rst(void)     
{                 
	
  DHT11_Mode(OUT);   //SET OUTPUT
  DHT11_Low;         //拉低DQ
  tim_delay_ms(20);      //主机拉低18~30ms
  DHT11_High;       //DQ=1 
  tim_delay_us(13);       //主机拉高10~35us
}
 
//等待DHT11的回应
//返回1:未检测到DHT11的存在
//返回0:存在
u8 DHT11_Check(void)      
{
  u8 retry=0;
  DHT11_Mode(IN);//SET INPUT   
  while (HAL_GPIO_ReadPin(DHT11_GPIO_PORT,DHT11_GPIO_PIN)&&retry<100)//DHT11会拉低40~80us
  {
    retry++;
    tim_delay_us(1);
  };   
  if(retry>=100)return 1;
  else retry=0;
    while (!HAL_GPIO_ReadPin(DHT11_GPIO_PORT,DHT11_GPIO_PIN)&&retry<100)//DHT11拉低后会再次拉高40~80us
  {
    retry++;
    tim_delay_us(1);
  };
  if(retry>=100)return 1;      
  return 0;
}
 
//从DHT11读取一个位
//返回值：1/0
u8 DHT11_Read_Bit(void)        
{
  u8 retry=0;
	DHT11_Mode(IN);
  while(HAL_GPIO_ReadPin(DHT11_GPIO_PORT,DHT11_GPIO_PIN)&&retry<100)//等待变为低电平
  {
    retry++;
    tim_delay_us(1);
  }
  retry=0;
  while(!HAL_GPIO_ReadPin(DHT11_GPIO_PORT,DHT11_GPIO_PIN)&&retry<100)//等待变高电平
  {
    retry++;
    tim_delay_us(1);
  }
  tim_delay_us(40);//等待40us
  if(HAL_GPIO_ReadPin(DHT11_GPIO_PORT,DHT11_GPIO_PIN))return 1;
  else return 0;       
}
 
//从DHT11读取一个字节
//返回值：读到的数据
u8 DHT11_Read_Byte(void)    
{        
  u8 i,dat;
  dat=0;
  for (i=0;i<8;i++) 
  {
    dat<<=1; 
    dat|=DHT11_Read_Bit();
  }                
  return dat;
}
//从DHT11读取一次数据
//temp:温度值(范围:0~50°)
//humi:湿度值(范围:20%~90%)
//返回值：0,正常;1,读取失败
u8 DHT11_Read_Data(u8 *temp,u8 *humi)    
{        
  u8 buf[5];
  u8 i;
  DHT11_Rst();
  if(DHT11_Check()==0)
  {
    for(i=0;i<5;i++)//读取40位数据
    {
      buf[i]=DHT11_Read_Byte();
    }
    if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
    {
      *humi=buf[0];
      *temp=buf[2];
    }
  }
  else return 1;
  return 0;      
}
 
//初始化DHT11的IO口 DQ 同时检测DHT11的存在
//返回1:不存在
//返回0:存在       
u8 DHT11_Init(void)
{   
//   GPIO_InitTypeDef  GPIO_InitStructure;  
//   RCC_APB2PeriphClockCmd(DHT11_GPIO_CLK, ENABLE);   //使能PA端口时钟
//   GPIO_InitStructure.GPIO_Pin = DHT11_GPIO_PIN;         //PG11端口配置
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
//   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//   GPIO_Init(DHT11_GPIO_PORT, &GPIO_InitStructure);         //初始化IO口
//   GPIO_SetBits(DHT11_GPIO_PORT,DHT11_GPIO_PIN);             //PG11 输出高
        
  DHT11_Rst();  //复位DHT11
  return DHT11_Check();//等待DHT11的回应
} 
void DHT11_Mode(u8 mode)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  if(mode)
  {
		DHT11_High;
    GPIO_InitStructure.Pin = DHT11_GPIO_PIN;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStructure.Pull = GPIO_NOPULL;
  }
  else
  {
		DHT11_High;
    GPIO_InitStructure.Pin =  DHT11_GPIO_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
		GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH; 
  }
  HAL_GPIO_Init(DHT11_GPIO_PORT, &GPIO_InitStructure);
}

u8 temp;
u8 humi;

void read_dh11_data()	
{
	tim_delay_ms(100);
	//读取温湿度
	DHT11_Read_Data(&temp,&humi);

  OLED_ShowString(2,1,"t:");
	OLED_ShowString(2,9,"H:");
	//显示温度数据
	
	OLED_ShowNum(2,3,temp,2);
	//显示湿度数据
	OLED_ShowNum(2,11,humi,2);                                

}



