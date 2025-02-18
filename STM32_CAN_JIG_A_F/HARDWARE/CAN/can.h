#ifndef __CAN_H
#define __CAN_H	 
#include "sys.h"	    
 //////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//CAN驱动 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/11
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

										 							 				    
u8 CAN_Mode_Init(u8 mode);//CAN初始化
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

















