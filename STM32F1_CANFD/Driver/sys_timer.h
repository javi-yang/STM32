#ifndef _SYS_TIMER_H_
#define _SYS_TIMER_H_


#define K1_PIN                        GPIO_Pin_3
#define K1_GPIO_PORT                  GPIOB 
#define K1_GPIO_CLK                   RCC_APB2Periph_GPIOB

#define K2_PIN                        GPIO_Pin_4
#define K2_GPIO_PORT                  GPIOB 
#define K2_GPIO_CLK                   RCC_APB2Periph_GPIOB

#define K3_PIN                        GPIO_Pin_5
#define K3_GPIO_PORT                  GPIOB 
#define K3_GPIO_CLK                   RCC_APB2Periph_GPIOB

#define LED1_PIN                      GPIO_Pin_7
#define LED1_GPIO_PORT                GPIOB 
#define LED1_GPIO_CLK                 RCC_APB2Periph_GPIOB

void Timer1_Config(void);
void TIM1_UP_IRQHandler(void);

#endif
