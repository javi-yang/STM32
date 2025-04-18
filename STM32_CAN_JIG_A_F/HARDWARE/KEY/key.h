#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK miniSTM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


//#define KEY0 PCin(5)   	
//#define KEY1 PAin(15)	 
//#define WK_UP  PAin(0)	 
 

//#define KEY0  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)
#define KEY_UP     GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键1
#define KEY_DOWN   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)//读取按键2 
#define WAKE_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)//读取按键2 
 

#define WAKE_UP_CAN	1		//KEY0  
#define KEY1_PRES	2		//KEY_UP 
#define WKUP_PRES	3		//KEY_DOWN  

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8 mode);  	//按键扫描函数					    
#endif
