/********************************************************************
filename : thl_data_struct_define.h
********************************************************************/


#ifndef _BSP_USART_H__
#define _BSP_USART_H__

#include <stdio.h>
#include "stm32f10x.h"


#define BAUD					115200		

#define RxBufferSize   500


extern uint8_t RxBuffer[RxBufferSize];
extern __IO uint16_t RxCounter; 
extern uint16_t NbrOfDataToRead;
extern uint8_t Rx_flag;

void usart_init(uint32_t baud_value);

void NVIC_config(void);


#endif

