#include "sys.h"
#include "math.h"
#include "usart.h"		
#include "delay.h"
#include "read.h" 
#include "timer.h"
#include "led.h"
#include "key.h"
#include "fall.h"
/**************************************************************************/
/******************************�������ϵͳ********************************/

/*       stm32��Сϵͳ�壬������MPU6050       */

/*�ܽ����ӣ�
		MPU6050                     ����2    RX��PA2  
											 TX��PA3
																			 
		����                        ����3    RX��PB10
											 TX��PB11
			
		������                       PA6
		
		����                         PA13
		
		ָʾ�� (����ʱ����������ʱ��˸)   PA8
			
*/

                                            

/**************************************************************************/
void System_init()
{
	Stm32_Clock_Init(9); 	//ϵͳʱ������
	LED_Init();
	KEY_Init();
	delay_init(72);	     	 //��ʱ��ʼ�� 
	uart_init(72,9600);	 	 //����1��ʼ��Ϊ9600 
	usart2_init(36,115200);  //����2��ʼ��Ϊ115200
	usart3_init(36,9600);  	 //����3��ʼ��Ϊ9600
	Timer4_Init(999,35999);  //0.5s
}

int main(void)
{		
	System_init();
	
	while(1)
	{
		fall_test(1.8,0.25,55);	  //��������㷨
	}	 
	
	return 0;
}





