/********************************************************************
filename : dev_can.h
discript : CAN�����ݶ��㴦��
********************************************************************/

#ifndef __DEV_CAN_H__
#define __DEV_CAN_H__

#include "stm32f10x.h"
#include "drv_canfdspi_api.h"
#include "drv_spi_mcp2517fd.h"
#include "typedefine.h"

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************


//! Use RX and TX Interrupt pins to check FIFO status
#define CAN_USE_RX_INT

#define MAX_TXQUEUE_ATTEMPTS 1

#define CAN_TRANS_SUCCESS	0
#define CAN_TRANS_FAIL		-1


#define CAN1_ALL_INT()	(!CAN1_INT())	
#define CAN1_TX_INT()		(!CAN1_TX())
#define CAN1_RX_INT()		(!CAN1_RX())



typedef struct{
	uint8_t	cmd[2];
	CAN_TX_MSGOBJ head;
	uint8_t				dat[64];
}CAN_TX_MSG;

//! CAN TX Message Object
typedef union _CAN_TX_FRAME {
	CAN_TX_MSG msg;
	uint8_t byte[74];
} CAN_TX_FRAME;


typedef struct{
	CAN_TX_MSGOBJ head;
	uint8_t				dat[8];
}CAN20_TX_MSG;

typedef struct{
	CAN_TX_MSGOBJ head;
	uint8_t				dat[64];
}CANFD_TX_MSG;


typedef struct{
	CAN_RX_MSGOBJ head;
	uint8_t				dat[64];
}CAN_RX_MSG;

typedef struct{
	CAN_RX_MSGOBJ head;
	uint8_t				dat[8];
}CAN20_RX_MSG;

typedef struct{
	CAN_RX_MSGOBJ head;
	uint8_t				dat[64];
}CANFD_RX_MSG;


// Transmit Channels
#define CAN_TX_FIFO CAN_FIFO_CH2

// Receive Channels
#define CAN_RX_FIFO CAN_FIFO_CH1



extern CAN_BUS_DIAGNOSTIC busDiagnostics;
extern uint8_t tec;
extern uint8_t rec;
extern CAN_ERROR_STATE errorFlags;
extern CAN_TX_FIFO_STATUS tx_status;
extern uint8_t can_rx_flag;




//Init CANFD
void etk_can_init(CAN_BITTIME_SETUP);

//Cfg MCP2517FD
void canfd_cfg_init(CAN_BITTIME_SETUP baud);

//Self test
void can_self_test(void);

//��鷢��FIFO�Ƿ�����
int8_t etk_can_transmit_check_fifo(CANFDSPI_MODULE_ID index);

//CAN send msg
int8_t can_transmit_msg(CANFDSPI_MODULE_ID index,CANFD_TX_MSG *tx_msg);

//Add message to transmit FIFO
void CAN_TransmitMessageQueue(CANFDSPI_MODULE_ID index);

//��ȡ����״̬�����
void read_can_bus_err_state(CANFDSPI_MODULE_ID index);


//Test SPI access
bool can1_test_register_access(void);

//Test RAM access
bool can1_test_ram_access(void);




#endif

