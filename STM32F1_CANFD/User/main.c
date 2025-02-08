/********************************************************************
filename : main.c
discript : STM32F1 CANFD driver
time     : 2023.11.15
淘宝店铺：云欧智能
例程：使用STM32F103C8T6 SPI2与MCP2518FD芯片进行通讯
Updated for AMP usage. 2025.1.7 YANG
********************************************************************/

#include "main.h"
#include "sys_phr.h"
#include "sys_timer.h"

void can_msg_transmit(void);
int8_t canfd_rcv_poll(void);


extern uint8_t tick;

uint16_t i = 0, j;
uint16_t d = 0x61;

int vol_data = 0x61;


CANFD_RX_MSG can_rx_msg;
CANFD_TX_MSG can_tx_msg;

void Uart1_SendData(unsigned char data);
int main(void)
{
    RCC_ClocksTypeDef RCC_Clocks;

    RCC_GetClocksFreq(&RCC_Clocks);
    SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);
    RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE ); //PORTB时钟使能
    System_Phr_Init();
    usart_init(115200);//调试串口
    Timer1_Config();
		//etk_can_init(CAN_1000K_4M);
    etk_can_init(CAN_500K_2M);		// YANG: changed to 500K/2M  数据波特率500K  CANFD初始化 //其他波特率参考“CAN_BITTIME_SETUP”参数，如果该参数中没有则需要查阅MCP2518FD数据手册自行配置
    printf("STM32F1 CANFD TEST\r\n");
    delay_10ms(50);
    can_tx_msg.head.word[0] = 0;
    can_tx_msg.head.word[1] = 0;

		
		while(1)
		{
			for(j = 0; j < 8; j++)  //YANG: wakeup message
            {

							    if(0) //IDE initialize  YANG:IDE not used, set to faulse
									{
										uint32_t id = (0x2B0) >> 18 & 0x7FF;
										id |= (0x2B0 & 0x3FFFF) << 11;
										can_tx_msg.head.word[0] = id;
									}
									else	//标准帧初始化帧头
									{
										can_tx_msg.head.bF.id.SID = 0x2B0;  //YANG: ID?? changed from 123 to 666
									}

									can_tx_msg.head.bF.ctrl.DLC = CAN_DLC_8;	//   YANG: changed from 64 to 8  长度参考“CAN_DLC”定义，不可以填定义里没有的参数
									can_tx_msg.head.bF.ctrl.IDE = 0;	// Extended CAN ID false
									can_tx_msg.head.bF.ctrl.RTR = 0;	// Remote frame
									can_tx_msg.head.bF.ctrl.BRS = TRUE;	//切换速率，也就是数据域启动高速率发送/接收
									can_tx_msg.head.bF.ctrl.FDF = TRUE;	// CAN FD							
							
								can_tx_msg.dat[0] = d;

            }

            can_msg_transmit();
			
			delay_10ms(20);

						for(j = 0; j < 8; j++)   //YANG: VOL setting message
            {
							if(0) //扩展帧初始化帧头  YANG:IDE not used, set to faulse
									{
										uint32_t id = (0x666) >> 18 & 0x7FF;
										id |= (0x666 & 0x3FFFF) << 11;
										can_tx_msg.head.word[0] = id;
									}
									else	//标准帧初始化帧头 YANG: Use standard
									{
										can_tx_msg.head.bF.id.SID = 0x666;  
									}

									can_tx_msg.head.bF.ctrl.DLC = CAN_DLC_8;	//   YANG: changed from 64 to 8  长度参考“CAN_DLC”定义，不可以填定义里没有的参数
									can_tx_msg.head.bF.ctrl.IDE = 0;	// Extended CAN ID false
									can_tx_msg.head.bF.ctrl.RTR = 0;	// Remote frame
									can_tx_msg.head.bF.ctrl.BRS = TRUE;	//切换速率，也就是数据域启动高速率发送/接收
									can_tx_msg.head.bF.ctrl.FDF = TRUE;	// CAN FD
							
							
									can_tx_msg.dat[0] = vol_data;  //YANG: Adjustable volumn data vol_data. Controlled by external key.

            }

            can_msg_transmit();
						
			delay_10ms(20);			
						
		}
			
}

/********************************************************************
function: can_rcv_poll
discript: CAN接收数据查询.
entrance: none.
return  : 读取的CAN消息数量
********************************************************************/
int8_t canfd_rcv_poll(void)
{
    int8_t pin, res = 0;
    CAN_RX_FIFO_EVENT 	rxFlags;
    pin = CAN1_RX_INT();

    if(pin)
    {
        do
        {

            DRV_CANFDSPI_ReceiveMessageGet(CANFD_CH1, CAN_RX_FIFO, &can_rx_msg.head, can_rx_msg.dat, MAX_DATA_BYTES);
            res = DRV_CANFDSPI_ReceiveChannelEventGet(CANFD_CH1, CAN_RX_FIFO, &rxFlags);
/*
            if(res < 0)
            {
                res = 0;
                break;
            }
*/
        }
        while(rxFlags & CAN_RX_FIFO_NOT_EMPTY_EVENT);

        can_rx_flag = TRUE;
    }

    return TRUE;
}


void can_msg_transmit(void)
{
    if(0 == etk_can_transmit_check_fifo(CANFD_CH1))
    {
        can_transmit_msg(CANFD_CH1, &can_tx_msg);
    }
}


