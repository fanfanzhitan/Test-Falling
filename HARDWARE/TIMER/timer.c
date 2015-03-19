#include "timer.h"
#include "sys.h"
#include "read.h"
#include "led.h"
volatile int time;

void Timer4_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<2;//TIM4ʱ��ʹ��    
 	TIM4->ARR=arr;  //�趨�������Զ���װֵ//�պ�1ms    
	TIM4->PSC=psc;  //Ԥ��Ƶ��72000,�õ�1Khz�ļ���ʱ��
	//����������Ҫͬʱ���òſ���ʹ���ж�
	TIM4->DIER|=1<<0;   //��������ж�				
	TIM4->DIER|=1<<6;   //�������ж�
		  							    
	//TIM4->CR1|=0x01;    //ʹ�ܶ�ʱ��3
  	MY_NVIC_Init(1,3,TIM4_IRQChannel,2);//��ռ1�������ȼ�3����2									 
}
extern u8 fall_flag;
void TIM4_IRQHandler(void)
{ 
	    		  			    
	if(TIM4->SR&0X0001)//����ж�
	{
			time++;	
			if(fall_flag == 1)
			{
				LED = ~LED;
			}
	}				   
	TIM4->SR&=~(1<<0);//����жϱ�־λ 	    
}
