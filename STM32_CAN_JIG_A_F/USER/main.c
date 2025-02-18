#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "can.h" 


 __IO uint32_t flag = 0;       //volatile Receive flag  
CanTxMsg TxMessage;		     //Tx buff zone
CanRxMsg RxMessage;				  // Rx buff zone
 					
static void can_delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
} 
 
int main(void)
 { 

	u16 tt=11,t=0;
//	u8 cnt=0;


//	u8 mode=CAN_Mode_LoopBack;//CAN工作模式;CAN_Mode_Normal(0)：普通模式，CAN_Mode_LoopBack(1)：环回模式
 
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口

	KEY_Init();				//按键初始化		 	
    CAN_ctrl();
	CAN_Mode_Init(0);
		    

	delay_init();	    	 //延时函数初始化	  
	//uart_init(9600);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口
	//CAN_SetMsgCOM0( &TxMessage);      // CAN WAKE COM
	//CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
 // can_delay(10000); 
     // can_delay(10000); 				
	
while(1)
{	
	KEY_Scan(0);
if(WAKE_UP==1)
{	 
	  if(t==0)
	  {t=1;
    CAN_SetMsgCOM1( &TxMessage);
	CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
	can_delay(10000);
	delay_ms(200);
	CAN_SetMsgCOM1( &TxMessage);
	CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
	can_delay(10000);
	delay_ms(200);
	CAN_SetMsgCOM1( &TxMessage);
	CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
	can_delay(10000);
	delay_ms(200);
	CAN_SetMsgCOM1( &TxMessage);
	CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
	can_delay(10000);
	delay_ms(200);
	CAN_SetMsgCOM1( &TxMessage);
	CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
	can_delay(10000);
	delay_ms(200);
	CAN_SetMsgCOM1( &TxMessage);
	CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
	can_delay(10000);
	delay_ms(200);
	CAN_SetMsgCOM1( &TxMessage);
	CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
	can_delay(10000);
	delay_ms(200);
	CAN_SetMsgCOM1( &TxMessage);
	CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
	can_delay(10000);
	delay_ms(200);
	CAN_SetMsgStd_BL010(&TxMessage);     // Set send content 
	CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
    can_delay(10000);                // wait send end
			  LED0=0;
			  LED1=0;
			  LED2=0;
			  LED3=0;
	
		  }			  
	 KEY_Scan(0);
	
				//CAN_SetMsgCOM0( &TxMessage);      // CAN WAKE COM
		//	CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
		 // can_delay(10000); 
     // can_delay(10000); 				
		 CAN_SetMsgCOM1( &TxMessage);
			CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
		  can_delay(10000);
     // can_delay(10000); 				
			// CAN_SetMsgCOM2( &TxMessage);
			//CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
		//	can_delay(10000);                // wait send end    
     // can_delay(10000); 				
		    LED5=!LED5;
			delay_ms(200);

			
    if(KEY_UP==0)                  // Press KEY0 to send data which mean the  bright UP
		{		if(tt<=11)tt++;
			else tt=11;
				if(tt==1){
			CAN_SetMsgStd_BL000(&TxMessage);    // Set send content 
			CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
		    can_delay(10000);                // wait send end
				LED0=1;
			  LED1=1;
			  LED2=1;
			  LED3=1;		
			}
			if(tt==2){
			CAN_SetMsgStd_BL001(&TxMessage);    // Set send content 
			CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
		    can_delay(10000);                // wait send end
				LED0=1;
			  LED1=0;
			  LED2=0;
			  LED3=1;		
			}
						if(tt==3){
			CAN_SetMsgStd_BL002(&TxMessage);     // Set send content 
			CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
		    can_delay(10000);                // wait send end
				LED0=0;
			  LED1=0;
			  LED2=0;
			  LED3=1;			
			}
						if(tt==4){
			CAN_SetMsgStd_BL003(&TxMessage);     // Set send content 
			CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
		    can_delay(10000);                // wait send end
				LED0=1;
			  LED1=1;
			  LED2=1;
			  LED3=0;
			}
							if(tt==5){
			CAN_SetMsgStd_BL004(&TxMessage);     // Set send content 
			CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
		    can_delay(10000);                // wait send end
				LED0=0;
			  LED1=1;
			  LED2=1;
			  LED3=0;
			}
						if(tt==6){
			CAN_SetMsgStd_BL005(&TxMessage);     // Set send content 
			CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
		    can_delay(10000);                // wait send end
				LED0=1;
			  LED1=0;
			  LED2=1;
			  LED3=0;
			}
							if(tt==7){
			CAN_SetMsgStd_BL006(&TxMessage);     // Set send content 
			CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
		    can_delay(10000);                // wait send end
				LED0=0;
			  LED1=0;
			  LED2=1;
			  LED3=0;
			}
			delay_ms(100);
	
 
					if(tt==8){
			CAN_SetMsgStd_BL007(&TxMessage);     // Set send content 
			CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
		    can_delay(10000);                // wait send end
				LED0=1;
			  LED1=1;
			  LED2=0;
			  LED3=0;
			}
						if(tt==9){
			CAN_SetMsgStd_BL008(&TxMessage);     // Set send content 
			CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
		    can_delay(10000);                // wait send end
				LED0=0;
			  LED1=1;
			  LED2=0;
			  LED3=0;
			}
			if(tt==10){
			CAN_SetMsgStd_BL009(&TxMessage);     // Set send content 
			CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
		    can_delay(10000);                // wait send end
				LED0=1;
			  LED1=0;
			  LED2=0;
			  LED3=0;
			}
		if(tt==11){
			CAN_SetMsgStd_BL010(&TxMessage);     // Set send content 
			CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
		    can_delay(10000);                // wait send end
			  LED0=0;
			  LED1=0;
			  LED2=0;
			  LED3=0;
			}
		}
		 if(KEY_DOWN==0)                  // Press KEY0 to send data which mean the  bright DOWN
		{	if(tt>0)tt--;else tt=1;
     if(tt==1){
			CAN_SetMsgStd_BL000(&TxMessage);    // Set send content 
			CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
		    can_delay(10000);                // wait send end
				LED0=1;
			  LED1=1;
			  LED2=1;
			  LED3=1;		
			}
			if(tt==2){
			CAN_SetMsgStd_BL001(&TxMessage);    // Set send content 
			CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
		    can_delay(10000);                // wait send end
				LED0=1;
			  LED1=0;
			  LED2=0;
			  LED3=1;		
			}
						if(tt==3){
			CAN_SetMsgStd_BL002(&TxMessage);     // Set send content 
			CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
		    can_delay(10000);                // wait send end
				LED0=0;
			  LED1=0;
			  LED2=0;
			  LED3=1;			
			}
						if(tt==4){
			CAN_SetMsgStd_BL003(&TxMessage);     // Set send content 
			CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
		    can_delay(10000);                // wait send end
				LED0=1;
			  LED1=1;
			  LED2=1;
			  LED3=0;
			}
							if(tt==5){
			CAN_SetMsgStd_BL004(&TxMessage);     // Set send content 
			CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
		    can_delay(10000);                // wait send end
				LED0=0;
			  LED1=1;
			  LED2=1;
			  LED3=0;
			}
						if(tt==6){
			CAN_SetMsgStd_BL005(&TxMessage);     // Set send content 
			CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
		    can_delay(10000);                // wait send end
				LED0=1;
			  LED1=0;
			  LED2=1;
			  LED3=0;
			}
							if(tt==7){
			CAN_SetMsgStd_BL006(&TxMessage);     // Set send content 
			CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
		    can_delay(10000);                // wait send end
				LED0=0;
			  LED1=0;
			  LED2=1;
			  LED3=0;
			}
			delay_ms(100);
	
 
					if(tt==8){
			CAN_SetMsgStd_BL007(&TxMessage);     // Set send content 
			CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
		    can_delay(10000);                // wait send end
				LED0=1;
			  LED1=1;
			  LED2=0;
			  LED3=0;
			}
						if(tt==9){
			CAN_SetMsgStd_BL008(&TxMessage);     // Set send content 
			CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
		    can_delay(10000);                // wait send end
				LED0=0;
			  LED1=1;
			  LED2=0;
			  LED3=0;
			}
			if(tt==10){
			CAN_SetMsgStd_BL009(&TxMessage);     // Set send content 
			CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
		    can_delay(10000);                // wait send end
				LED0=1;
			  LED1=0;
			  LED2=0;
			  LED3=0;
			}
		if(tt==11){
			CAN_SetMsgStd_BL010(&TxMessage);     // Set send content 
			CAN_Transmit(CAN1, &TxMessage);  // Send content transmit
		    can_delay(10000);                // wait send end
			  LED0=0;
			  LED1=0;
			  LED2=0;
			  LED3=0;
			}
		}
		
	 	delay_ms(10);
		}
	

else 
{   t=0;
    LED0=!LED0;
	LED1=!LED1;
	LED2=!LED2;
	LED3=!LED3;
	delay_ms(100);

}	

}


}




