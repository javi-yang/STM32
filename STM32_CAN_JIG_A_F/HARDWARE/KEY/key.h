#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK miniSTM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


//#define KEY0 PCin(5)   	
//#define KEY1 PAin(15)	 
//#define WK_UP  PAin(0)	 
 

//#define KEY0  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)
#define KEY_UP     GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ����1
#define KEY_DOWN   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)//��ȡ����2 
#define WAKE_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)//��ȡ����2 
 

#define WAKE_UP_CAN	1		//KEY0  
#define KEY1_PRES	2		//KEY_UP 
#define WKUP_PRES	3		//KEY_DOWN  

void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8 mode);  	//����ɨ�躯��					    
#endif
