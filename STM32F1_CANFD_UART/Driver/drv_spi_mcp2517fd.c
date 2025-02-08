/********************************************************************
filename : spi_mcp2517fd.c
discript : can driver
********************************************************************/
/********************************************************************
discript : STM32F1 CANFD driver
time     : 2023.11.15
淘宝店铺：云欧智能
例程：使用STM32F103C8T6 SPI2与MCP2518FD芯片进行通讯
********************************************************************/

#include "drv_spi_mcp2517fd.h"


inline int8_t spi_master_transfer(uint8_t *SpiTxData, uint8_t *SpiRxData, uint16_t spiTransferSize);



void spi1_gpio_config(void)	
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );//PORTA时钟使能 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5| GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //PA5/6/7复用推挽输出 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);						//初始化GPIOA
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7); 
}

void can_hd_spi_port_init(void)//hardware spi  72M/4=18Mbit
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    SPI_InitTypeDef  SPI_InitStructure;
    //   /* SPI1 configuration */
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStructure);
    SPI_Cmd(SPI1, ENABLE); //使能SPI外设
}


uint8_t SPI1_ReadWriteByte(uint8_t TxData)
{
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) {}
    SPI_I2S_SendData(SPI1, TxData);
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET) {}
    return SPI_I2S_ReceiveData(SPI1);
}


/*******************************************************************************
* Function Name  : DRV_SPI_TransferData(void)
* Description    : SPI 数据读写
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int8_t DRV_SPI_TransferData(uint8_t spiSlaveDeviceIndex, uint8_t *SpiTxData, uint8_t *SpiRxData, uint16_t spiTransferSize)
{
    return spi1_master_transfer(SpiTxData, SpiRxData, spiTransferSize);
}

int8_t spi1_master_transfer(uint8_t *SpiTxData, uint8_t *SpiRxData, uint16_t size)
{
    uint16_t pos = 0;

    CAN1_SPI_CS_LOW();
    __NOP();

    while(pos < size)
    {
        SpiRxData[pos] = SPI1_ReadWriteByte(SpiTxData[pos]);
        pos++;
    }

    __NOP();
    CAN1_SPI_CS_HIGH();

    return 0;
}

/********************************************************************
function: uint8_t spi_read_byte(void)
discript: Reads a byte from the SPI.
          This function must be used only if the Start_Read_Sequence
          function has been previously called.
entrance: none
return  : Byte Read from the SPI Flash.
other   : none
********************************************************************/


/********************************************************************
function: uint8_t spi_send_byte(uint8_t byte)
discript: Sends a byte through the SPI interface and return the byte
          received from the SPI bus.
entrance: byte : byte to send.
return  : The value of the received byte.
other   : none
********************************************************************
uint8_t spi1_send_byte(uint8_t byte)
{
  // Loop while DR register in not emplty
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

  // Send byte through the SPI peripheral
  SPI_I2S_SendData(SPI1, byte);

  // Wait to receive a byte
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

  // Return the byte read from the SPI bus
  return SPI_I2S_ReceiveData(SPI1);
}
*/




