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
/******************************跌到检测系统********************************/

/*       stm32最小系统板，蓝牙，MPU6050       */

/*管脚连接：
		MPU6050                     串口2    RX：PA2  
											 TX：PA3
																			 
		蓝牙                        串口3    RX：PB10
											 TX：PB11
			
		蜂鸣器                       PA6
		
		按键                         PA13
		
		指示灯 (正常时长亮，跌倒时闪烁)   PA8
			
*/

                                            

/**************************************************************************/
void System_init()
{
	Stm32_Clock_Init(9); 	//系统时钟设置
	LED_Init();
	KEY_Init();
	delay_init(72);	     	 //延时初始化 
	uart_init(72,9600);	 	 //串口1初始化为9600 
	usart2_init(36,115200);  //串口2初始化为115200
	usart3_init(36,9600);  	 //串口3初始化为9600
	Timer4_Init(999,35999);  //0.5s
}

int main(void)
{		
	System_init();
	
	while(1)
	{
		fall_test(1.8,0.25,55);	  //跌到检测算法
	}	 
	
	return 0;
}





