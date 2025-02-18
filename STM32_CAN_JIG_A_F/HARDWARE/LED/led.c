#include "led.h"

 
	    
//LED BL初始化
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);	
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	  
 GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_OD ; 		 
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8				
 GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); 
		
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;  
 GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_OD ; 		 
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8				
 GPIO_SetBits(GPIOC,GPIO_Pin_6|GPIO_Pin_7); 			
	
	
	



 
	
}
 
