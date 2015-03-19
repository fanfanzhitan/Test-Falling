#include "sys.h"
#include "math.h"
#include "usart.h"		
#include "delay.h"
#include "read.h" 
#include "timer.h"
#include "led.h"
#include "key.h"
#include "fall.h"


extern volatile int time;
extern float SVM;                //融合阈值
extern float ANGLE; 
u8 fall_flag = 0;
void fall_test(float TH1,float TH2,float angle)
{
	u8 key;
	int i,flag = 1;	
	float angle0,angle1;
	    
	LED= 0;               	//灯亮，程序正常运行
	fall_flag = 0;	
	
	read_mpu_acc();			//读取加速度
	read_mpu_angle();
	angle0 = ANGLE;
	
	if((SVM-0.00)>TH1)    	//疑似跌倒，进行检测
	{
		//printf("疑似跌倒\n");
		delay_ms(1000);
		
		for(i=0;i<10&&flag==1;i++)
		{
			read_mpu_acc();
			if(fabs(SVM-1.00)>TH2)
				flag = 0;   	//疑似运动
			delay_ms(100);
		}
		if(flag==1)
		{
			//printf("进一步确认跌倒\n");
			//进一步分析摔倒姿态，进行最后确认
			read_mpu_angle();
			angle1 = ANGLE;
		    if(fabs(angle1 - angle0) > angle)
			{ 
				 TIM4->CR1|=0x01;    //使能定时器4
				 time = 0;    
				 //printf("\n请按键否认跌倒!!\n"); 
				 Sound = 1;              //蜂鸣器发声
				 while(time<30)
				 {
					key = KEY_Scan(); 
					delay_ms(10);
					if(key == 1)
					{
						key = 0;
						Sound = 0;              //蜂鸣器不发声
						//printf("否认跌倒！！\n");
						 TIM4->CR1&=~0x01;    //使能定时器4
						return;
					}
				  }
				
				 if(time==30)			//15秒内无按键
				 {
					key = 0;
					while(key == 0)
					{
						printf("确认跌倒\n");
						//发送急救信号
						USART3_Translate();
						Sound = 1;              //蜂鸣器发声
						fall_flag = 1;
						key =(u8)KEY_Scan();
						delay_ms(10);
					}
					Sound = 0;
					TIM4->CR1&=~0x01;    //使能定时器4
				 }
				   
			 }
			 else
			 {
				printf("不是跌倒！！\n");
			 }
		 }
			 
		 if(flag==0)
		 {
			 printf("进一步检测不是跌倒\n");
			 flag = 1;
		 }
		 
		}
		 
}
