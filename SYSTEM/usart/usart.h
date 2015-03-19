#ifndef __USART_H
#define __USART_H
#include <stm32f10x_map.h>
#include <stm32f10x_nvic.h>
#include "stdio.h"	 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/5/27
//�汾��V1.3
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
////////////////////////////////////////////////////////////////////////////////// 	  
 
	  	
extern u8 USART_RX_BUF[64];     //���ջ���,���63���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8 USART_RX_STA;         //����״̬���
extern u8 USART2_RX_BUF[11];     //���ջ���,���11���ֽ� 
extern u8 USART2_RX_STA;         //����״̬���	


//����봮���жϽ��գ��벻Ҫע�����º궨��
#define EN_USART1_RX //ʹ�ܴ���1����
#define EN_USART2_RX
#define EN_USART3_RX
void uart_init(u32 pclk2,u32 bound);
void usart2_init(u32 pclk1,u32 bound);
void usart3_init(u32 pclk1,u32 bound);
void USART3_Translate(void);
#endif	   
















