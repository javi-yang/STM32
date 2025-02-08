
#include "stm32f10x.h"
#include <cstdlib>
#include "drv_spi_mcp2517fd.h"
#include "sys_timer.h"
/********************************************************************
discript : STM32F1 CANFD driver
time     : 2023.11.15
淘宝店铺：云欧智能
例程：使用STM32F103C8T6 SPI2与MCP2518FD芯片进行通讯
********************************************************************/


void System_Phr_Init()
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_15;		 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;		 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	//PD1必须重映射才能作为输出
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_PinRemapConfig(GPIO_Remap_PD01,ENABLE);
  //// PB3默认JTAG口,需关闭，否则无法输出
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = CAN1_RX_PIN|K1_PIN|K2_PIN|K3_PIN; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(CAN1_RX_GPIO_PORT, &GPIO_InitStructure);
}

