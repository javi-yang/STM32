#ifndef __UART_TASK_H
#define	__UART_TASK_H

#include "stm32f1xx_hal.h"

extern uint8_t uart1_analysis_flag;
extern uint8_t uart3_analysis_flag;

void init_uart1(uint32_t baud);
void init_uart3(uint32_t baud);
void protocol_analysis(uint8_t * data, uint8_t len);

#endif
