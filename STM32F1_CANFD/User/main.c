/********************************************************************
filename : main.c
discript : STM32F1 CANFD driver
time     : 2023.11.15
�Ա����̣���ŷ����
���̣�ʹ��STM32F103C8T6 SPI2��MCP2518FDоƬ����ͨѶ
Updated for AMP usage. 2025.4.17 YANG
********************************************************************/

#include "main.h"
#include "sys_phr.h"
#include "sys_timer.h"

void can_msg_transmit(void);
int8_t canfd_rcv_poll(void);

extern uint8_t tick;

uint16_t i = 0, j;
uint16_t d = 0x61;

int amp_vol = 0x0071;


CANFD_RX_MSG can_rx_msg;
CANFD_TX_MSG can_tx_msg;

void Uart1_SendData(unsigned char data);
int main(void)
{
    RCC_ClocksTypeDef RCC_Clocks;

    RCC_GetClocksFreq(&RCC_Clocks);
    SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
    System_Phr_Init();
    usart_init(115200); // ���Դ���
    Timer1_Config();
    // etk_can_init(CAN_1000K_4M);
    etk_can_init(CAN_500K_2M); // YANG: changed to 500K/2M
    printf("STM32F1 CANFD TEST\r\n");
    delay_10ms(5);
    can_tx_msg.head.word[0] = 0;
    can_tx_msg.head.word[1] = 0;

    can_msg_transmit();

    while (1)
    {
        etk_can_init(CAN_500K_2M); // YANG: changed to 500K/2M
        for (j = 0; j < 5; j++)    // YANG: wakeup message
        {
            can_tx_msg.head.bF.id.SID = 0x2B0; // YANG: ID?? changed from 123 to 666

            can_tx_msg.head.bF.ctrl.DLC = CAN_DLC_8; //   YANG: changed from 64 to 8  
            can_tx_msg.head.bF.ctrl.IDE = 0;         // Extended CAN ID false
            can_tx_msg.head.bF.ctrl.RTR = 0;         // Remote frame
            can_tx_msg.head.bF.ctrl.BRS = TRUE;      
            can_tx_msg.head.bF.ctrl.FDF = TRUE;      // CAN FD

            can_tx_msg.dat[0] = d;
            can_tx_msg.dat[1] = d;
            can_tx_msg.dat[2] = d;
            can_tx_msg.dat[3] = d;

            can_msg_transmit();

            delay_10ms(30);

            can_tx_msg.head.bF.id.SID = 0x666;

            can_tx_msg.head.bF.ctrl.DLC = CAN_DLC_8; //   YANG: changed from 64 to 8  
            can_tx_msg.head.bF.ctrl.IDE = 0;         // Extended CAN ID false
            can_tx_msg.head.bF.ctrl.RTR = 0;         // Remote frame
            can_tx_msg.head.bF.ctrl.BRS = TRUE;      
            can_tx_msg.head.bF.ctrl.FDF = TRUE;      // CAN FD

            can_tx_msg.dat[0] = amp_vol & 0x00FF; 
            can_tx_msg.dat[1] = (amp_vol & 0xFF00) >> 8; 

            can_msg_transmit();

            delay_10ms(30);

        }


    }
}

/********************************************************************
function: can_rcv_poll
discript: CAN�������ݲ�ѯ.
entrance: none.
return  : ��ȡ��CAN��Ϣ����
********************************************************************/
int8_t canfd_rcv_poll(void)
{
    int8_t pin, res = 0;
    CAN_RX_FIFO_EVENT rxFlags;
    pin = CAN1_RX_INT();

    if (pin)
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
        } while (rxFlags & CAN_RX_FIFO_NOT_EMPTY_EVENT);

        can_rx_flag = TRUE;
    }

    return TRUE;
}

void can_msg_transmit(void)
{
    if (0 == etk_can_transmit_check_fifo(CANFD_CH1))
    {
        can_transmit_msg(CANFD_CH1, &can_tx_msg);
    }
}
