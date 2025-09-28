//https://item.taobao.com/item.htm?id=718212632480

#include "common.h"

extern uint8_t update_flag;

uint32_t mill_tick = 0, one_mill = 0;
uint32_t send_rate_tick = 0,scr_refresh_tick=0;
extern uint8_t current_ch_index;
void process_key()
{
	static uint16_t IN3,IN3_1,IN3_2,IN3_3,
								 IN4,IN4_1,IN4_2,IN4_3,IN5,IN5_1,IN5_2,IN5_3;
/**************************************K1****************************************************************/
    IN3_2=HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);
    if(IN3_1==1&&IN3_2==0)
      IN3=1;
    if(IN3_1==0&&IN3_2==1)
    {
      IN3=0;
      if(IN3_3>=20&&IN3_3<2000)
      {
				xMacInfo.k1_flag=0x01;
      }
      IN3_3=0;
    }
    IN3_1=IN3_2;
    if(IN3==1)IN3_3++;
/**************************************K2****************************************************************/
    IN4_2=HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);
      if(IN4_1==1&&IN4_2==0)
        IN4=1;
      if(IN4_1==0&&IN4_2==1)
      {
        IN4=0;
        if(IN4_3>=10&&IN4_3<2000)
        {
          xMacInfo.k2_flag=0x01;
        }
        IN4_3=0;
      }
      IN4_1=IN4_2;
      if(IN4==1)IN4_3++;
/**************************************K3****************************************************************/
    IN5_2=HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4);
      if(IN5_1==1&&IN5_2==0)
        IN5=1;
      if(IN5_1==0&&IN5_2==1)
      {
        IN5=0;
        if(IN5_3>=10&&IN5_3<2000)
        {
          current_ch_index++;
					if(current_ch_index>=3)
					{
						current_ch_index=0;
					}
					xMacInfo.show_once_ch_title=0;
        }
        IN5_3=0;
      }
      IN5_1=IN5_2;
      if(IN5==1)IN5_3++;   		
	
}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM2)  /* tim2 1ms*/
    {
        if(++send_rate_tick >= xMacInfo.uart_send_rate)
        {
            send_rate_tick = 0;
            xMacInfo.uart_send_flag = 1;
        }
				if(++scr_refresh_tick>=xMacInfo.scr_refresh_rate)
				{
						scr_refresh_tick = 0;
            xMacInfo.scr_refresh_flag = 1;
				}
        if(++mill_tick >= 500)
        {
            mill_tick = 0;

            if(++one_mill >= 1000)
            {
                one_mill = 0;
            }

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
        }
				process_key();
    }
}
