/********************************************************************
discript : STM32F1 CANFD driver
time     : 2023.11.15
�Ա����̣���ŷ����
���̣�ʹ��STM32F103C8T6 SPI2��MCP2518FDоƬ����ͨѶ
********************************************************************/

#include "stm32f10x.h"
#include "delay.h"
#include "sys_phr.h"
#include "stdio.h"
#include "sys_timer.h"
#include "dev_can.h"
#include "main.h"

void can_msg_transmit(void);
uint32_t LED_SHICK =500,led_status_cout=0,OneMill=0,MillSecond=0;
extern CANFD_TX_MSG can_tx_msg;


void Timer1_Config()
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
	NVIC_InitTypeDef NVIC_InitStructure;  
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_TimeBaseStructure.TIM_Period=1000-1;
  TIM_TimeBaseStructure.TIM_Prescaler= 64-1;
  TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
  TIM_ClearFlag(TIM1, TIM_FLAG_Update);
  TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
  TIM_Cmd(TIM1, ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
}

void send_canfd_test()
{
	can_tx_msg.head.word[0] = 0;
	can_tx_msg.head.word[1] = 0;
	if(1) //��չ֡��ʼ��֡ͷ
	{
			uint32_t id = (0x12345678)>>18 & 0x7FF;
			id |= (0x12345678 & 0x3FFFF)<<11;
			can_tx_msg.head.word[0] = id;
	}
	else	//��׼֡��ʼ��֡ͷ
	{
			can_tx_msg.head.bF.id.SID = 0x123;
	}
	can_tx_msg.head.bF.ctrl.DLC = CAN_DLC_64;	//���Ȳο���CAN_DLC�����壬�����������û�еĲ���
	can_tx_msg.head.bF.ctrl.IDE = 1;	// Extended CAN ID false
	can_tx_msg.head.bF.ctrl.RTR = 0;	// Remote frame
	can_tx_msg.head.bF.ctrl.BRS = TRUE;	//�л����ʣ�Ҳ�������������������ʷ���/����
	can_tx_msg.head.bF.ctrl.FDF = TRUE;	// CAN FD
	for(int j=0;j<64;j++)
	{
		can_tx_msg.dat[j] = j;
	}
	can_msg_transmit();
}

void send_canfd_k2_test()//��ͳCAN
{
	static uint8_t send_tick=0;
	if(++send_tick>0xFF)
	{
		send_tick=0;
	}
	can_tx_msg.head.word[0] = 0;
	can_tx_msg.head.word[1] = 0;
	if(1) //��չ֡��ʼ��֡ͷ
	{
			uint32_t id = (0x12345678)>>18 & 0x7FF;
			id |= (0x12345678 & 0x3FFFF)<<11;
			can_tx_msg.head.word[0] = id;
	}
	else	//��׼֡��ʼ��֡ͷ
	{
			can_tx_msg.head.bF.id.SID = 0x123;
	}
	can_tx_msg.head.bF.ctrl.DLC = CAN_DLC_8;	//���Ȳο���CAN_DLC�����壬�����������û�еĲ���
	can_tx_msg.head.bF.ctrl.IDE = 1;	// Extended CAN ID false
	can_tx_msg.head.bF.ctrl.RTR = 0;	// Remote frame
	can_tx_msg.head.bF.ctrl.BRS = FALSE;	//�л����ʣ�Ҳ�������������������ʷ���/����
	can_tx_msg.head.bF.ctrl.FDF = FALSE;	//TRUE->CAN FD
	for(int j=0;j<8;j++)
	{
		can_tx_msg.dat[j] = j+1;
	}
	can_tx_msg.dat[7]=send_tick;
	can_msg_transmit();
}

void send_canfd_k3_test()
{
	static uint8_t send_tick=0;
	if(++send_tick>0xFF)
	{
		send_tick=0;
	}
	can_tx_msg.head.word[0] = 0;
	can_tx_msg.head.word[1] = 0;
	if(1) //��չ֡��ʼ��֡ͷ
	{
			uint32_t id = (0x12345678)>>18 & 0x7FF;
			id |= (0x12345678 & 0x3FFFF)<<11;
			can_tx_msg.head.word[0] = id;
	}
	else	//��׼֡��ʼ��֡ͷ
	{
			can_tx_msg.head.bF.id.SID = 0x123;
	}
	can_tx_msg.head.bF.ctrl.DLC = CAN_DLC_8;	//���Ȳο���CAN_DLC�����壬�����������û�еĲ���
	can_tx_msg.head.bF.ctrl.IDE = 1;	// Extended CAN ID false
	can_tx_msg.head.bF.ctrl.RTR = 0;	// Remote frame
	can_tx_msg.head.bF.ctrl.BRS = TRUE;	//BRS(Bit Rate Switch)λ����ת�����أ���BRSΪ����λʱ���ݶε�λ�������ٲöε�λ����һ�£���BRSΪ����λʱ���ݶε�λ���ʸ����ٲöε�λ����
	can_tx_msg.head.bF.ctrl.FDF = TRUE;	// CAN FD
	for(int j=0;j<8;j++)
	{
		can_tx_msg.dat[j] = j+1;
	}
	can_tx_msg.dat[7]=send_tick;
	can_msg_transmit();
}

void process_key()
{
	static uint16_t IN3,IN3_1,IN3_2,IN3_3,
								 IN4,IN4_1,IN4_2,IN4_3,IN5,IN5_1,IN5_2,IN5_3;
/**************************************K1****************************************************************/
    


	IN3_2=GPIO_ReadInputDataBit(K1_GPIO_PORT, K1_PIN);
    if(IN3_1==1&&IN3_2==0)
      IN3=1;
    if(IN3_1==0&&IN3_2==1)
    {
      IN3=0;
      if(IN3_3>=10&&IN3_3<3000)
      {
        printf("KKK1 press\r\n");
				
				
				if(vol_data <= 0x01)
				{
					vol_data = 0x01;
				}
				else
				{
					vol_data -= 0x10;
				}
				//send_canfd_test();
      }
      IN3_3=0;
    }
    IN3_1=IN3_2;
    if(IN3==1)IN3_3++;
/**************************************K2****************************************************************/
    IN4_2=GPIO_ReadInputDataBit(K2_GPIO_PORT, K2_PIN);
      if(IN4_1==1&&IN4_2==0)
        IN4=1;
      if(IN4_1==0&&IN4_2==1)
      {
        IN4=0;
        if(IN4_3>=10&&IN4_3<3000)
        {
          printf("k2 press\r\n");
					
					vol_data += 0x10;
					
					if(vol_data > 0xF1)
					{
						vol_data = 0xF1;
					}
					
					//send_canfd_k2_test();
        }
        IN4_3=0;
      }
      IN4_1=IN4_2;
      if(IN4==1)IN4_3++;
/**************************************K3****************************************************************/
    IN5_2=GPIO_ReadInputDataBit(K3_GPIO_PORT, K3_PIN);
      if(IN5_1==1&&IN5_2==0)
        IN5=1;
      if(IN5_1==0&&IN5_2==1)
      {
        IN5=0;
        if(IN5_3>=10&&IN5_3<3000)
        {
          printf("k3 press\r\n");
					
					vol_data = 0x61;
					//send_canfd_k3_test();
        }
        IN5_3=0;
      }
      IN5_1=IN5_2;
      if(IN5==1)IN5_3++;   		
	
}

/********************************״ָ̬ʾ��****************************************/
void status_led_shake()
{
		static uint32_t led_status_cout=0;
		if(++led_status_cout>=0xffff)
		{
			led_status_cout=0;
		}
		if(led_status_cout<LED_SHICK)  
		{
			GPIO_SetBits(LED1_GPIO_PORT, LED1_PIN);
		}
		else if(led_status_cout>=LED_SHICK&&led_status_cout<LED_SHICK*2)
		{
			GPIO_ResetBits(LED1_GPIO_PORT, LED1_PIN);
		}
		else if(led_status_cout>LED_SHICK*3)
		{
			led_status_cout=0;
		}  
}

/*************************1ms timer irq******************************************************/
void TIM1_UP_IRQHandler()
{
  if ( TIM_GetITStatus( TIM1, TIM_IT_Update) != RESET ) 
  {
    TIM_ClearFlag(TIM1, TIM_IT_Update ); 
/*************************timer***********************************************/
		if(MillSecond++>1000)
		{
			MillSecond=0;
			if(OneMill<0xFFFF)OneMill++;
		}
/*************************key and led******************************************************/		
		status_led_shake();
		process_key();
  }
}




















