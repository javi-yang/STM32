#include "can.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//CAN���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/11
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
//CAN��ʼ��
//tsjw:����ͬ����Ծʱ�䵥Ԫ.��Χ:1~3; CAN_SJW_1tq	 CAN_SJW_2tq CAN_SJW_3tq CAN_SJW_4tq
//tbs2:ʱ���2��ʱ�䵥Ԫ.��Χ:1~8;
//tbs1:ʱ���1��ʱ�䵥Ԫ.��Χ:1~16;	  CAN_BS1_1tq ~CAN_BS1_16tq
//brp :�����ʷ�Ƶ��.��Χ:1~1024;(ʵ��Ҫ��1,Ҳ����1~1024) tq=(brp)*tpclk1
//ע�����ϲ����κ�һ����������Ϊ0,�������.
//������=Fpclk1/((tsjw+tbs1+tbs2)*brp);
//mode:0,��ͨģʽ;1,�ػ�ģʽ;
//Fpclk1��ʱ���ڳ�ʼ����ʱ������Ϊ36M,�������CAN_Normal_Init(1,8,7,5,1);
//������Ϊ:36M/((1+8+7)*5)=450Kbps    1 3 4      9
//����ֵ:0,��ʼ��OK;
//    ����,��ʼ��ʧ��;


extern __IO uint32_t flag ;		 //���ڱ�־�Ƿ���յ����ݣ����жϺ����и�ֵ
extern CanRxMsg RxMessage;				 //���ջ�����







void CAN_ctrl(void){


 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);	
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;	 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //CANEN  CAN STANDBY
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 
 GPIO_SetBits(GPIOA,GPIO_Pin_8|GPIO_Pin_9);						


}
	
	
	
	
	
u8 CAN_Mode_Init(u8 mode)
{

	GPIO_InitTypeDef GPIO_InitStructure; 
	CAN_InitTypeDef        CAN_InitStructure;
 	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��PORTAʱ��	                   											 

  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);//ʹ��CAN1ʱ��	

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);		//��ʼ��IO
   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��IO
	
	
		/* Configure one bit for preemption priority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		   
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			   
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	

	  
 	//CAN��Ԫ����
   	CAN_InitStructure.CAN_TTCM=DISABLE;						 //��ʱ�䴥��ͨ��ģʽ  //
 	CAN_InitStructure.CAN_ABOM=DISABLE;						 //����Զ����߹���	 //
  	CAN_InitStructure.CAN_AWUM=DISABLE;						 //˯��ģʽͨ���������(���CAN->MCR��SLEEPλ)//
  	CAN_InitStructure.CAN_NART=DISABLE;						 	//��ֹ�����Զ����� //
  	CAN_InitStructure.CAN_RFLM=DISABLE;						 //���Ĳ�����,�µĸ��Ǿɵ� // 
  	CAN_InitStructure.CAN_TXFP=DISABLE;						 //���ȼ��ɱ��ı�ʶ������ //
  	CAN_InitStructure.CAN_Mode= 0;	         //ģʽ���ã� mode:0,��ͨģʽ;1,�ػ�ģʽ; //
  	//	CAN Baudrate = 500 kBps  (CAN Clock APB 1 = 36 MHz) 
  	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;				
  	CAN_InitStructure.CAN_BS1=CAN_BS1_8tq; 
  	CAN_InitStructure.CAN_BS2=CAN_BS2_7tq;
  	CAN_InitStructure.CAN_Prescaler=18		;            ////BTR-BRP    36/(1+4+4) /8=500kbps
  	CAN_Init(CAN1, &CAN_InitStructure);            // ��ʼ��CAN1 

   


		CAN_FilterInitStructure.CAN_FilterNumber=1;	  //������0
		CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 
		CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit; //32λ 
		CAN_FilterInitStructure.CAN_FilterIdHigh=0x5ae0; //((((u32)0x01E3406A<<3)|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF0000)>>16;	//	0x01E3406A 
		CAN_FilterInitStructure.CAN_FilterIdLow=0x5a00; //(((u32)0x01E3406A<<3)|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF;  
		CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0xffff;//32λMASK
		CAN_FilterInitStructure.CAN_FilterMaskIdLow=0xffff;
		CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FilterFIFO0;//������0������FIFO0
		CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //���������0
       	CAN_FilterInit(&CAN_FilterInitStructure);//�˲�����ʼ��
		
		
		/*CAN_FilterInitStructure.CAN_FilterNumber=0;	  //������0
		CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdList; 
		CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_16bit; //32λ 
		CAN_FilterInitStructure.CAN_FilterIdHigh=0;
		CAN_FilterInitStructure.CAN_FilterIdLow=(((u32)0x5A4<<3)|CAN_ID_STD|CAN_RTR_DATA)&0xFFFF; 
		CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//32λMASK
		CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
		CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FilterFIFO0;//������0������FIFO0
		CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //���������0
								
		CAN_FilterInit(&CAN_FilterInitStructure);//�˲�����ʼ��

	
	 		CAN_FilterInitStructure.CAN_FilterNumber=2;	  //������0
		CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 
		CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; //32λ 
		CAN_FilterInitStructure.CAN_FilterIdHigh= ((((u32)0x1E340000<<3)|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF0000)>>16;
		CAN_FilterInitStructure.CAN_FilterIdLow=  (((u32)0x1E340000<<3)|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF;  
		CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//32λMASK
		CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
		CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_FilterFIFO0;//������0������FIFO0
		CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //���������0
								
		CAN_FilterInit(&CAN_FilterInitStructure);//�˲�����ʼ��
	
	
	
	/*CAN_FilterInitStructure.CAN_FilterNumber=0;	  //������0
 	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 
  	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; //32λ 
  	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;////32λID
  	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
  	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//32λMASK
  	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
  	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;//������0������FIFO0
 	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //���������0

  	CAN_FilterInit(&CAN_FilterInitStructure);//�˲�����ʼ��
	*/
	
	/*CAN_IT ENABLE*/
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
	
	return 0;
}
		
void CAN_SetMsgCOM0(CanTxMsg *TxMessage)
{	  
	
					 
  TxMessage->ExtId=0x1E340003;					 
  TxMessage->IDE=CAN_ID_EXT;				 // EXT
  TxMessage->RTR=CAN_RTR_DATA;		  //data will be send
  TxMessage->DLC=2;							    //data long8
		
	TxMessage->Data[0] =0;
	TxMessage->Data[1] =0;


}		

void CAN_SetMsgCOM1(CanTxMsg *TxMessage)
{	  


					 
  TxMessage->ExtId=0x1E340000;					 
  TxMessage->IDE=CAN_ID_EXT;				 // EXT
  TxMessage->RTR=CAN_RTR_DATA;		  //data will be send
  TxMessage->DLC=6;							    //data long8
		

	TxMessage->Data[0] =0;
	TxMessage->Data[1] =02;
	TxMessage->Data[2] =0;
	TxMessage->Data[3] =0;
	TxMessage->Data[4] =0;
	TxMessage->Data[5] =0;



}

void CAN_SetMsgCOM2(CanTxMsg *TxMessage)
{	  


					 
  TxMessage->ExtId=0x1E340000;					 
  TxMessage->IDE=CAN_ID_EXT;				 // EXT
  TxMessage->RTR=CAN_RTR_DATA;		  //data will be send
  TxMessage->DLC=6;							    //data long8
			
	TxMessage->Data[0] =0;
	TxMessage->Data[1] =06;
	TxMessage->Data[2] =0;
	TxMessage->Data[3] =0;
	TxMessage->Data[4] =0;
	TxMessage->Data[5] =0;

}

void CAN_SetMsgStd(CanTxMsg *TxMessage)
{	  

	TxMessage->StdId=0x503;					 
  TxMessage->IDE=CAN_ID_STD;				 // EXT
  TxMessage->RTR=CAN_RTR_DATA;		  //data will be send
  TxMessage->DLC=8;							    //data long8
	
	delay_ms(1);	
	
	TxMessage->Data[0] =0;
	TxMessage->Data[1] =0;
	TxMessage->Data[2] =0;
	TxMessage->Data[3] =0;
	TxMessage->Data[4] =0;
	TxMessage->Data[5] =0;
  TxMessage->Data[6] =0xC8;
	TxMessage->Data[7] =0;
	
	 	delay_ms(1);	
	
}
void CAN_SetMsgStd_BL000(CanTxMsg *TxMessage)
{	  

	TxMessage->StdId=0x503;					 
  TxMessage->IDE=CAN_ID_STD;				 // EXT
  TxMessage->RTR=CAN_RTR_DATA;		  //data will be send
  TxMessage->DLC=8;							    //data long8
	
	delay_ms(1);	
	
	TxMessage->Data[0] =0;
	TxMessage->Data[1] =0;
	TxMessage->Data[2] =0;
	TxMessage->Data[3] =0;
	TxMessage->Data[4] =0;
	TxMessage->Data[5] =0;
  TxMessage->Data[6] =0;
	TxMessage->Data[7] =0;
	
	 	delay_ms(1);	
	
}
void CAN_SetMsgStd_BL001(CanTxMsg *TxMessage)
{	  

	TxMessage->StdId=0x503;					 
  TxMessage->IDE=CAN_ID_STD;				 // EXT
  TxMessage->RTR=CAN_RTR_DATA;		  //data will be send
  TxMessage->DLC=8;							    //data long8
	
	delay_ms(1);	
	
	TxMessage->Data[0] =0;
	TxMessage->Data[1] =0;
	TxMessage->Data[2] =0;
	TxMessage->Data[3] =0;
	TxMessage->Data[4] =0;
	TxMessage->Data[5] =0;
  TxMessage->Data[6] =0x14;
	TxMessage->Data[7] =0;
	
	 	delay_ms(1);	
	
}

void CAN_SetMsgStd_BL002(CanTxMsg *TxMessage)
{	  

	TxMessage->StdId=0x503;					 
  TxMessage->IDE=CAN_ID_STD;				 // EXT
  TxMessage->RTR=CAN_RTR_DATA;		  //data will be send
  TxMessage->DLC=8;							    //data long8
	
	delay_ms(1);	
	
	TxMessage->Data[0] =0;
	TxMessage->Data[1] =0;
	TxMessage->Data[2] =0;
	TxMessage->Data[3] =0;
	TxMessage->Data[4] =0;
	TxMessage->Data[5] =0;
  TxMessage->Data[6] =0x28;
	TxMessage->Data[7] =0;
	
	 	delay_ms(1);	
	
}

void CAN_SetMsgStd_BL003(CanTxMsg *TxMessage)
{	  

	TxMessage->StdId=0x503;					 
  TxMessage->IDE=CAN_ID_STD;				 // EXT
  TxMessage->RTR=CAN_RTR_DATA;		  //data will be send
  TxMessage->DLC=8;							    //data long8
	
	delay_ms(1);	
	
	TxMessage->Data[0] =0;
	TxMessage->Data[1] =0;
	TxMessage->Data[2] =0;
	TxMessage->Data[3] =0;
	TxMessage->Data[4] =0;
	TxMessage->Data[5] =0;
  TxMessage->Data[6] =0x3c;
	TxMessage->Data[7] =0;
	
	 	delay_ms(1);	
	
}
void CAN_SetMsgStd_BL004(CanTxMsg *TxMessage)
{	  

	TxMessage->StdId=0x503;					 
  TxMessage->IDE=CAN_ID_STD;				 // EXT
  TxMessage->RTR=CAN_RTR_DATA;		  //data will be send
  TxMessage->DLC=8;							    //data long8
	
	delay_ms(1);	
	
	TxMessage->Data[0] =0;
	TxMessage->Data[1] =0;
	TxMessage->Data[2] =0;
	TxMessage->Data[3] =0;
	TxMessage->Data[4] =0;
	TxMessage->Data[5] =0;
  TxMessage->Data[6] =0x50;
	TxMessage->Data[7] =0;
	
	 	delay_ms(1);	
	
}
void CAN_SetMsgStd_BL005(CanTxMsg *TxMessage)
{	  

	TxMessage->StdId=0x503;					 
  TxMessage->IDE=CAN_ID_STD;				 // EXT
  TxMessage->RTR=CAN_RTR_DATA;		  //data will be send
  TxMessage->DLC=8;							    //data long8
	
	delay_ms(1);	
	
	TxMessage->Data[0] =0;
	TxMessage->Data[1] =0;
	TxMessage->Data[2] =0;
	TxMessage->Data[3] =0;
	TxMessage->Data[4] =0;
	TxMessage->Data[5] =0;
  TxMessage->Data[6] =0x64;
	TxMessage->Data[7] =0;
	
	 	delay_ms(1);	
	
}
void CAN_SetMsgStd_BL006(CanTxMsg *TxMessage)
{	  

	TxMessage->StdId=0x503;					 
  TxMessage->IDE=CAN_ID_STD;				 // EXT
  TxMessage->RTR=CAN_RTR_DATA;		  //data will be send
  TxMessage->DLC=8;							    //data long8
	
	delay_ms(1);	
	
	TxMessage->Data[0] =0;
	TxMessage->Data[1] =0;
	TxMessage->Data[2] =0;
	TxMessage->Data[3] =0;
	TxMessage->Data[4] =0;
	TxMessage->Data[5] =0;
  TxMessage->Data[6] =0x78;
	TxMessage->Data[7] =0;
	
	 	delay_ms(1);	
	
}
void CAN_SetMsgStd_BL007(CanTxMsg *TxMessage)
{	  

	TxMessage->StdId=0x503;					 
  TxMessage->IDE=CAN_ID_STD;				 // EXT
  TxMessage->RTR=CAN_RTR_DATA;		  //data will be send
  TxMessage->DLC=8;							    //data long8
	
	delay_ms(1);	
	
	TxMessage->Data[0] =0;
	TxMessage->Data[1] =0;
	TxMessage->Data[2] =0;
	TxMessage->Data[3] =0;
	TxMessage->Data[4] =0;
	TxMessage->Data[5] =0;
  TxMessage->Data[6] =0x8c;
	TxMessage->Data[7] =0;
	
	 	delay_ms(1);	
	
}
void CAN_SetMsgStd_BL008(CanTxMsg *TxMessage)
{	  

	TxMessage->StdId=0x503;					 
  TxMessage->IDE=CAN_ID_STD;				 // EXT
  TxMessage->RTR=CAN_RTR_DATA;		  //data will be send
  TxMessage->DLC=8;							    //data long8
	
	delay_ms(1);	
	
	TxMessage->Data[0] =0;
	TxMessage->Data[1] =0;
	TxMessage->Data[2] =0;
	TxMessage->Data[3] =0;
	TxMessage->Data[4] =0;
	TxMessage->Data[5] =0;
  TxMessage->Data[6] =0xa0;
	TxMessage->Data[7] =0;
	
	 	delay_ms(1);	
	
}
void CAN_SetMsgStd_BL009(CanTxMsg *TxMessage)
{	  

	TxMessage->StdId=0x503;					 
  TxMessage->IDE=CAN_ID_STD;				 // EXT
  TxMessage->RTR=CAN_RTR_DATA;		  //data will be send
  TxMessage->DLC=8;							    //data long8
	
	delay_ms(1);	
	
	TxMessage->Data[0] =0;
	TxMessage->Data[1] =0;
	TxMessage->Data[2] =0;
	TxMessage->Data[3] =0;
	TxMessage->Data[4] =0;
	TxMessage->Data[5] =0;
  TxMessage->Data[6] =0xb4;
	TxMessage->Data[7] =0;
	
	 	delay_ms(1);	
	
}
void CAN_SetMsgStd_BL010(CanTxMsg *TxMessage)
{	  

	TxMessage->StdId=0x503;					 
  TxMessage->IDE=CAN_ID_STD;				 // EXT
  TxMessage->RTR=CAN_RTR_DATA;		  //data will be send
  TxMessage->DLC=8;							    //data long8
	
	delay_ms(1);	
	
	TxMessage->Data[0] =0;
	TxMessage->Data[1] =0;
	TxMessage->Data[2] =0;
	TxMessage->Data[3] =0;
	TxMessage->Data[4] =0;
	TxMessage->Data[5] =0;
  TxMessage->Data[6] =0xc8;
	TxMessage->Data[7] =0;
	
	 	delay_ms(1);	
	
}



void CAN_SetMsg(CanTxMsg *TxMessage,uint8_t abc)
{	  
	uint8_t ubCounter = 0;

					 
  TxMessage->ExtId=0x1E340000;					 
  TxMessage->IDE=CAN_ID_EXT;				 // EXT
  TxMessage->RTR=CAN_RTR_DATA;		  //data will be send
  TxMessage->DLC=8;							    //data long8
	
	
	TxMessage->Data[1] =04;
	TxMessage->Data[5] =01;
	for (ubCounter = 0; ubCounter < 8; ubCounter++)
  {
    TxMessage->Data[ubCounter] = abc;
  }
}

 

void Init_RxMes(CanRxMsg *RxMessage)
{
  uint8_t ubCounter = 0;

	
  RxMessage->StdId = 0x5A4;
  RxMessage->ExtId = 0x01E3406A;
  RxMessage->IDE = CAN_ID_STD;
  RxMessage->DLC = 8;
  RxMessage->FMI = 0;
  for (ubCounter = 0; ubCounter < 8; ubCounter++)
  {
    RxMessage->Data[ubCounter] = 0x00;
  }
}













