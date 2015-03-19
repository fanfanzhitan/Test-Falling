#include "timer.h"
#include "sys.h"
#include "read.h"
#include "led.h"
volatile int time;

void Timer4_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<2;//TIM4时钟使能    
 	TIM4->ARR=arr;  //设定计数器自动重装值//刚好1ms    
	TIM4->PSC=psc;  //预分频器72000,得到1Khz的计数时钟
	//这两个东东要同时设置才可以使用中断
	TIM4->DIER|=1<<0;   //允许更新中断				
	TIM4->DIER|=1<<6;   //允许触发中断
		  							    
	//TIM4->CR1|=0x01;    //使能定时器3
  	MY_NVIC_Init(1,3,TIM4_IRQChannel,2);//抢占1，子优先级3，组2									 
}
extern u8 fall_flag;
void TIM4_IRQHandler(void)
{ 
	    		  			    
	if(TIM4->SR&0X0001)//溢出中断
	{
			time++;	
			if(fall_flag == 1)
			{
				LED = ~LED;
			}
	}				   
	TIM4->SR&=~(1<<0);//清除中断标志位 	    
}
