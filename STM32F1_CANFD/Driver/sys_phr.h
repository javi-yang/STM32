#ifndef _SYS_PHR_H_
#define _SYS_PHR_H_

#include "stm32f10x.h"

void System_Power_Init(void);
void Phr_GPIO_Init(void);
void Init_NVIC(void);
void SystemClk_Init(void);
void System_Phr_Init(void);
#endif


