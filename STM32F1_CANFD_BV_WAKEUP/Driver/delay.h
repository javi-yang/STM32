/********************************************************************
filename : delay.h
********************************************************************/

#ifndef _DELAY_H__
#define _DELAY_H__

#include "stm32f10x.h"

void delay_10ms(__IO uint32_t nTime);

void delay_s(uint16_t nCount);

/*-------------------------------------------------------*/
//private function
void TimingDelay_Decrement(void);


#endif




