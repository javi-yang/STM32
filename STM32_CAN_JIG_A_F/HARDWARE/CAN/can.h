#ifndef __CAN_H
#define __CAN_H	 
#include "sys.h"	    
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

										 							 				    
u8 CAN_Mode_Init(u8 mode);//CAN��ʼ��
void CAN_ctrl(void);
void CAN_SetMsg(CanTxMsg *TxMessage,uint8_t abc);
void Init_RxMes(CanRxMsg *RxMessage);
void CAN_SetMsgCOM0(CanTxMsg *TxMessage);
void CAN_SetMsgCOM1(CanTxMsg *TxMessage);
void CAN_SetMsgCOM2(CanTxMsg *TxMessage);
void CAN_SetMsgStd(CanTxMsg *TxMessage);
void CAN_SetMsgStd_BL000(CanTxMsg *TxMessage);
void CAN_SetMsgStd_BL001(CanTxMsg *TxMessage);
void CAN_SetMsgStd_BL002(CanTxMsg *TxMessage);
void CAN_SetMsgStd_BL003(CanTxMsg *TxMessage);
void CAN_SetMsgStd_BL004(CanTxMsg *TxMessage);
void CAN_SetMsgStd_BL005(CanTxMsg *TxMessage);
void CAN_SetMsgStd_BL006(CanTxMsg *TxMessage);
void CAN_SetMsgStd_BL007(CanTxMsg *TxMessage);
void CAN_SetMsgStd_BL008(CanTxMsg *TxMessage);
void CAN_SetMsgStd_BL009(CanTxMsg *TxMessage);
void CAN_SetMsgStd_BL010(CanTxMsg *TxMessage);
	


#endif

















