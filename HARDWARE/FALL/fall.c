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
extern float SVM;                //�ں���ֵ
extern float ANGLE; 
u8 fall_flag = 0;
void fall_test(float TH1,float TH2,float angle)
{
	u8 key;
	int i,flag = 1;	
	float angle0,angle1;
	    
	LED= 0;               	//������������������
	fall_flag = 0;	
	
	read_mpu_acc();			//��ȡ���ٶ�
	read_mpu_angle();
	angle0 = ANGLE;
	
	if((SVM-0.00)>TH1)    	//���Ƶ��������м��
	{
		//printf("���Ƶ���\n");
		delay_ms(1000);
		
		for(i=0;i<10&&flag==1;i++)
		{
			read_mpu_acc();
			if(fabs(SVM-1.00)>TH2)
				flag = 0;   	//�����˶�
			delay_ms(100);
		}
		if(flag==1)
		{
			//printf("��һ��ȷ�ϵ���\n");
			//��һ������ˤ����̬���������ȷ��
			read_mpu_angle();
			angle1 = ANGLE;
		    if(fabs(angle1 - angle0) > angle)
			{ 
				 TIM4->CR1|=0x01;    //ʹ�ܶ�ʱ��4
				 time = 0;    
				 //printf("\n�밴�����ϵ���!!\n"); 
				 Sound = 1;              //����������
				 while(time<30)
				 {
					key = KEY_Scan(); 
					delay_ms(10);
					if(key == 1)
					{
						key = 0;
						Sound = 0;              //������������
						//printf("���ϵ�������\n");
						 TIM4->CR1&=~0x01;    //ʹ�ܶ�ʱ��4
						return;
					}
				  }
				
				 if(time==30)			//15�����ް���
				 {
					key = 0;
					while(key == 0)
					{
						printf("ȷ�ϵ���\n");
						//���ͼ����ź�
						USART3_Translate();
						Sound = 1;              //����������
						fall_flag = 1;
						key =(u8)KEY_Scan();
						delay_ms(10);
					}
					Sound = 0;
					TIM4->CR1&=~0x01;    //ʹ�ܶ�ʱ��4
				 }
				   
			 }
			 else
			 {
				printf("���ǵ�������\n");
			 }
		 }
			 
		 if(flag==0)
		 {
			 printf("��һ����ⲻ�ǵ���\n");
			 flag = 1;
		 }
		 
		}
		 
}
