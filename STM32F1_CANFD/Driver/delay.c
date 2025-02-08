/********************************************************************
filename : delay.c
discript : This file offer some delay function use systerm tick.
********************************************************************/
/********************************************************************
discript : STM32F1 CANFD driver
time     : 2023.11.15
�Ա����̣���ŷ����
���̣�ʹ��STM32F103C8T6 SPI2��MCP2518FDоƬ����ͨѶ
********************************************************************/

#include "delay.h"

static __IO uint32_t TimingDelay_basic;

void delay_s(uint16_t nCount)
{
	for(; nCount>0; nCount--)
		delay_10ms(100);
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 10 ms.
  * @retval None
  */
void delay_10ms(__IO uint32_t nTime)
{
  TimingDelay_basic = nTime;

  while(TimingDelay_basic != 0);
}


/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay_basic != 0x00)
  { 
    TimingDelay_basic --;
  }
}

