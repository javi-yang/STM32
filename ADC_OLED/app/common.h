/**************************************************************************************************
  File name: common.h
  Version:   1.0
  Date:      2023/2/1
  https://item.taobao.com/item.htm?id=718212632480
**************************************************************************************************/

#ifndef _COMMON_H_
#define _COMMON_H_


#include "main.h"
#include <string.h>
#include "stdlib.h"
#include <stdio.h>
#include "logic.h"
#include "oled.h"
#include "bmp.h"

#define SEND_RATE  50  //MS


#define UART1_MAX_LEN 100
#define UART2_MAX_LEN 100
#define UART3_MAX_LEN 100



#define U32Bit0     ((u32)0x00000001)
#define U32Bit1     ((u32)0x00000002)
#define U32Bit2     ((u32)0x00000004)
#define U32Bit3     ((u32)0x00000008)
#define U32Bit4     ((u32)0x00000010)
#define U32Bit5     ((u32)0x00000020)
#define U32Bit6     ((u32)0x00000040)
#define U32Bit7     ((u32)0x00000080)
#define U32Bit8     ((u32)0x00000100)
#define U32Bit9     ((u32)0x00000200)
#define U32Bit10    ((u32)0x00000400)
#define U32Bit11    ((u32)0x00000800)
#define U32Bit12    ((u32)0x00001000)
#define U32Bit13    ((u32)0x00002000)
#define U32Bit14    ((u32)0x00004000)
#define U32Bit15    ((u32)0x00008000)
#define U32Bit16    ((u32)0x00010000)
#define U32Bit17    ((u32)0x00020000)
#define U32Bit18    ((u32)0x00040000)
#define U32Bit19    ((u32)0x00080000)
#define U32Bit20    ((u32)0x00100000)
#define U32Bit21    ((u32)0x00200000)
#define U32Bit22    ((u32)0x00400000)
#define U32Bit23    ((u32)0x00800000)
#define U32Bit24    ((u32)0x01000000)
#define U32Bit25    ((u32)0x02000000)
#define U32Bit26    ((u32)0x04000000)
#define U32Bit27    ((u32)0x08000000)
#define U32Bit28    ((u32)0x10000000)
#define U32Bit29    ((u32)0x20000000)
#define U32Bit30    ((u32)0x40000000)
#define U32Bit31    ((u32)0x80000000)


typedef struct
{
    uint16_t usLen;
    uint8_t  ucData[UART1_MAX_LEN];
} xSerial1Object_t;

typedef struct
{
    uint16_t usLen;
    uint8_t  ucData[UART3_MAX_LEN];
} xSerial3Object_t;

typedef struct
{
    uint8_t mode_index;
    uint16_t uart_send_rate;
		uint8_t  uart_send_flag;
		uint16_t scr_refresh_rate;
		uint8_t scr_refresh_flag;
		uint8_t show_once_ch_title;
		uint8_t k1_flag;
		uint8_t k2_flag;
		uint8_t k3_flag;
} xMacInfo_t;

extern TIM_HandleTypeDef htim2;
extern xMacInfo_t xMacInfo;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart3_rx;

extern xSerial1Object_t xSerial1;
extern xSerial3Object_t xSerial3;
extern ADC_HandleTypeDef hadc1;

#endif

