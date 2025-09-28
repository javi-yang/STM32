//https://item.taobao.com/item.htm?id=718212632480

#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdlib.h>

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
/***************************************************************/
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart1, (uint8_t*)&ch,1,10);
	//HAL_UART_Transmit(&huart3, (uint8_t*)&ch,1,10);
  return ch;
}
 
#pragma import(__use_no_semihosting)
struct __FILE
{
  int handle;
};
 
FILE __stdout;
 
void _sys_exit(int x)
{
  x = x;
}


