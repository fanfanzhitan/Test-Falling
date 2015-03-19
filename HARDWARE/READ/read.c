#include "math.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "read.h"



extern u8 USART2_RX_BUF[11];     //���ܻ��壬11���ֽ�
extern u8 count;              	 //��¼�ֽڸ���
extern volatile u8 sign;         //����״̬
float SVM;
float ANGLE;

void read_mpu_acc()         //��ȡmpu�ļ��ٶ�
{
	int i=0,num_Acc=0;
	float svm;
	static double acc[3];
	
	SVM = 0;  //��ʼ��SVM
	
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
					SVM = SVM/5.00;    		//5�������ֵ��ƽ��ֵ
					printf("SVM:%7.2f \n",SVM);
					break;
				}
				switch(USART2_RX_BUF[1])
				{
					case 0x51:	//���ٶ�����
								num_Acc++;
								acc[0] = (short)(USART2_RX_BUF[3]<<8|USART2_RX_BUF[2])/32768.0*16; 	
								acc[1] = (short)(USART2_RX_BUF[5]<<8|USART2_RX_BUF[4])/32768.0*16; 	
								acc[2] = (short)(USART2_RX_BUF[7]<<8|USART2_RX_BUF[6])/32768.0*16;
								svm = sqrt(acc[0]*acc[0]+acc[1]*acc[1]+acc[2]*acc[2]);
								SVM+=svm;                       //�����ֵ���
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

void read_mpu_angle()        //��ȡmpu�ĽǶ�
{
	int i=0,num_Angle=0;
	static double angle[3];
	
	ANGLE = 0; //�Ƕȳ�ʼ��
	
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
					ANGLE = ANGLE/5.00;    //5����Ƕȵ�ƽ��ֵ
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
