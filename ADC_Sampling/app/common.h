/**************************************************************************************************
  File name: common.h
  Version:   1.0
  Date:      2025/2/1
  https://item.taobao.com/item.htm?id=717251001647
**************************************************************************************************/

#ifndef _COMMON_H_
#define _COMMON_H_


#include "main.h"
#include <string.h>
#include "stdlib.h"
#include <stdio.h>
#include "logic.h"
#include "uart_task.h"
#include "save_info.h"

#define UART1_MAX_LEN 100
#define UART3_MAX_LEN 100


typedef struct
{
    uint16_t usLen;
    uint8_t  ucData[UART1_MAX_LEN];
}xSerial1Object_t;


typedef struct
{
    uint16_t usLen;
    uint8_t  ucData[UART3_MAX_LEN];
}xSerial3Object_t;

typedef struct
{
    uint8_t mode_index;
		uint8_t  select_m1ch;
    uint8_t  select_m2ch;
		uint32_t  baud;
		uint32_t send_rate;
}xMacInfo_t;


extern TIM_HandleTypeDef htim2;
extern xMacInfo_t xMacInfo;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart3_rx;

extern xSerial1Object_t xSerial1;
extern xSerial3Object_t xSerial3;

#endif

