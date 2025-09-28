#ifndef _LG_TIMER_H_
#define _LG_TIMER_H_


#include "common.h"

#define DFLT_10MS_TIMER_CNTR_NUM     10                // the total value of 10ms timer counter.  

typedef struct
{
    uint8_t uc10msTimrCntrNum;      // 0    numbers of timer counter for 10ms timer counter.
    int32_t iT10msTimer[DFLT_10MS_TIMER_CNTR_NUM];    // {-1} the array for 10ms timer counter
} TIMERGEN;
extern TIMERGEN tmr;

#define TIMER_DEFAULTS {DFLT_10MS_TIMER_CNTR_NUM, {-1,-1,-1,-1,-1,}}

#define TIMER_UPLOAD_TEM   iT10msTimer[0]     /* ÉÏ´«ÎÂ¶È 5s */
#define TIMER_CHECK_HEART  iT10msTimer[1]     /* ÐÄÌø¼ì²â 1s */
#define TIMER_UPLOAD_RELAY iT10msTimer[2]     /* ¼ÌµçÆ÷×´Ì¬ 5s */


#define LED_ERROR_ON  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET)
#define LED_ERROR_OFF HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET)


#define M1_ON  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET)
#define M1_OFF HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET)

#define M2_ON  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET)
#define M2_OFF HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET)

#define M3_ON  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET)
#define M3_OFF HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET)

#define M4_ON  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET)
#define M4_OFF HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET)

#define M5_ON  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET)
#define M5_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET)

#define M6_ON  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET)
#define M6_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET)

#define M7_ON  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET)
#define M7_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET)

#define M8_ON  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET)
#define M8_OFF HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET)

#define M9_ON  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET)
#define M9_OFF HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET)

#define M10_ON  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET)
#define M10_OFF HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET)


void lg_timer(void *parameter);
void Motor_Ctrl(uint8_t channel, uint8_t en);

#endif

