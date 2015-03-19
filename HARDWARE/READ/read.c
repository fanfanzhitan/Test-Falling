#include "math.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "read.h"



extern u8 USART2_RX_BUF[11];     //接受缓冲，11个字节
extern u8 count;              	 //记录字节个数
extern volatile u8 sign;         //接受状态
float SVM;
float ANGLE;

void read_mpu_acc()         //读取mpu的加速度
{
	int i=0,num_Acc=0;
	float svm;
	static double acc[3];
	
	SVM = 0;  //初始化SVM
	
	while(1)
	{	
		if(sign)
		{
			i = 0;
			sign = 0;
			if(USART2_RX_BUF[0] == 0x55)
			{
				if(num_Acc==5)
				{
					SVM = SVM/5.00;    		//5次求得阈值的平均值
					printf("SVM:%7.2f \n",SVM);
					break;
				}
				switch(USART2_RX_BUF[1])
				{
					case 0x51:	//加速度数据
								num_Acc++;
								acc[0] = (short)(USART2_RX_BUF[3]<<8|USART2_RX_BUF[2])/32768.0*16; 	
								acc[1] = (short)(USART2_RX_BUF[5]<<8|USART2_RX_BUF[4])/32768.0*16; 	
								acc[2] = (short)(USART2_RX_BUF[7]<<8|USART2_RX_BUF[6])/32768.0*16;
								svm = sqrt(acc[0]*acc[0]+acc[1]*acc[1]+acc[2]*acc[2]);
								SVM+=svm;                       //多次阈值相加
								break;	  
					
					default:  break;	  
				}
			}
		}
		else
		{
			i++;
			if(i == 1000)
			{
				printf("mpu6050 error!");
				return;
			}
		}
	}	
}

void read_mpu_angle()        //读取mpu的角度
{
	int i=0,num_Angle=0;
	static double angle[3];
	
	ANGLE = 0; //角度初始化
	
	while(1)
	{	
		if(sign)
		{
			i = 0;
			sign = 0;
			if(USART2_RX_BUF[0] == 0x55)
			{
				if(num_Angle==5)
				{
					ANGLE = ANGLE/5.00;    //5次求角度的平均值
					printf("ANGLE:%7.2f \n",ANGLE);
					break;
				}
				switch(USART2_RX_BUF[1])
				{
					case 0x53: 
								num_Angle++;
								angle[0] = (short)(USART2_RX_BUF[3]<<8|USART2_RX_BUF[2])/32768.0*180; 	//R
								angle[1] = (short)(USART2_RX_BUF[5]<<8|USART2_RX_BUF[4])/32768.0*180; 	//p
								angle[2] = (short)(USART2_RX_BUF[7]<<8|USART2_RX_BUF[6])/32768.0*180;	//y
								ANGLE += angle[0];
								break;
					default:  break;	  
				}
			}
         }	
		else
		{
			i++;
			if(i == 1000)
			{
				printf("mpu6050 error!");
				return;
			}
		}
	}
	
}
