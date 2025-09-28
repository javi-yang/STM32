//https://item.taobao.com/item.htm?id=717251001647
#include "common.h"

#define FLASH_MACINFO_ADDR 0x0800FC00  // 指定的 Flash 地址

uint8_t uart1_analysis_flag;
uint8_t uart3_analysis_flag;

extern uint32_t ADC_BUF[10];

/**
 * @brief 初始化UART1串口通信
 * 
 * @param baud 波特率设置（单位：bps）
 * 
 * @note 配置参数说明：
 *       - Instance:       使用USART1外设
 *       - BaudRate:       用户指定的波特率
 *       - WordLength:     8位数据位
 *       - StopBits:       1位停止位
 *       - Parity:         无校验位
 *       - Mode:           TX和RX双工模式
 *       - HwFlowCtl:      无硬件流控
 *       - OverSampling:   16倍过采样（标准配置）
 * 
 * @note 初始化流程：
 *       1. 填充UART初始化结构体参数
 *       2. 调用HAL_UART_Init()应用配置
 *       3. 初始化失败时触发Error_Handler()
 * 
 * @warning 调用前需确保：
 *       - 已启用USART1时钟（__HAL_RCC_USART1_CLK_ENABLE()）
 *       - GPIO已配置为复用功能（TX:PA9, RX:PA10 for STM32F1）
 *       - 波特率（110-1000000bps）
 */
void init_uart1(uint32_t baud)
{
    huart1.Instance = USART1;
    huart1.Init.BaudRate = baud;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler();
    }
}

void init_uart3(uint32_t baud)
{
    huart3.Instance = USART3;
    huart3.Init.BaudRate = baud;
    huart3.Init.WordLength = UART_WORDLENGTH_8B;
    huart3.Init.StopBits = UART_STOPBITS_1;
    huart3.Init.Parity = UART_PARITY_NONE;
    huart3.Init.Mode = UART_MODE_TX_RX;
    huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart3.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart3) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief 协议解析函数，处理接收到的AT指令并执行相应操作
 * 
 * @param data 接收到的数据缓冲区（以uint8_t数组形式存储的AT指令字符串）
 * @param len  数据长度（指令字符串的有效长度）
 * 
 * @note 支持的AT指令格式：
 *       - "AT"                  : 简单测试指令，回复"OK"
 *       - "AT+MODE=<mode>"      : 设置工作模式（0~4）
 *       - "AT+M1CH=<channel>"   : 设置M1通道（0~9），并强制切到模式3
 *       - "AT+M2CH=<channel>"   : 设置M2通道（0~9），并强制切到模式4
 *       - "AT+BAUD=<baudrate>"  : 设置串口波特率（110~1000000）
 *       - "AT+RATE=<rate>"      : 设置发送速率（0~10000）
 * 
 * @note 所有成功操作均会保存配置到Flash，并回复"OK"；失败则回复"ERROR"。
 */
void protocol_analysis(uint8_t * data, uint8_t len)
{
    if (strncmp((char*)data, "AT", 2) == 0 && len <= 4)
    {
        printf("OK\n");
    }
    // 解析AT+MODE=?指令
    else if (strncmp((char*)data, "AT+MODE=", 8) == 0 && len <= 15)
    {
        int mode = atoi((char*)data + 8);

        if (mode < 5)
        {
            xMacInfo.mode_index = mode;
            save_xMacInfo_to_flash();
            printf("OK\n");
        }
        else
        {
            printf("ERROR\n");
        }
    }
    // 解析AT+M1CH=?指令
    else if (strncmp((char*)data, "AT+M1CH=", 8) == 0 && len <= 15)
    {
        int channel = atoi((char*)data + 8);

        if (channel >= 0 && channel <= 9)
        {
            xMacInfo.select_m1ch = channel;
            xMacInfo.mode_index = 0x03;
            save_xMacInfo_to_flash();
            printf("OK\n");
        }
        else
        {
            printf("ERROR\n");
        }
    }
    // 解析AT+M2CH=?指令
    else if (strncmp((char*)data, "AT+M2CH=", 8) == 0 && len <= 15)
    {
        int channel = atoi((char*)data + 8);

        if (channel >= 0 && channel <= 9)
        {
            xMacInfo.select_m2ch = channel;
            xMacInfo.mode_index = 0x04;
            save_xMacInfo_to_flash();
            printf("OK\n");
        }
        else
        {
            printf("ERROR\n");
        }
    }
    // 解析AT+BAUD=?指令
    else if (strncmp((char*)data, "AT+BAUD=", 8) == 0 && len <= 20)
    {
        int baud = atoi((char*)data + 8);

        if (baud >= 110 && baud <= 1000000)
        {
            xMacInfo.baud = baud;
            save_xMacInfo_to_flash();
            printf("OK\n");
        }
        else
        {
            printf("ERROR\n");
        }
    }
    // 解析AT+RATE=?指令
    else if (strncmp((char*)data, "AT+RATE=", 8) == 0 && len <= 20)
    {
        int rate = atoi((char*)data + 8);

        if (rate >= 0 && rate <= 10000)
        {
            xMacInfo.send_rate = rate;
            save_xMacInfo_to_flash();
            printf("OK\n");
        }
        else
        {
            printf("ERROR\n");
        }
    }
}

/**
 * @brief UART1空闲中断回调函数，用于处理接收完成的数据
 * 
 * @param huart UART句柄指针（此处固定为huart1）
 * 
 * @note 功能说明：
 *       1. 检测UART1空闲中断标志（IDLE）
 *       2. 清除空闲中断标志（防止重复进入）
 *       3. 读取状态寄存器(SR)和数据寄存器(DR)以清除潜在错误标志
 *       4. 停止DMA接收（防止数据覆盖）
 *       5. 计算实际接收数据长度（总缓存长度 - 剩余DMA计数器值）
 *       6. 置位分析标志位（uart1_analysis_flag）
 *       7. 调用协议解析函数处理数据（protocol_analysis）
 *       8. 清空接收缓冲区
 *       9. 重新启动DMA接收（循环接收模式）
 * 
 */
void UART1_IDLE_Callback(UART_HandleTypeDef *huart)
{
    if( __HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE) != RESET)
    {
        __HAL_UART_CLEAR_IDLEFLAG(&huart1);
        uint32_t temp = huart1.Instance->SR;
        temp = huart1.Instance->DR;
        HAL_UART_DMAStop(&huart1);
        temp  = hdma_usart1_rx.Instance->CNDTR;
        xSerial1.usLen =  UART1_MAX_LEN - temp;
        uart1_analysis_flag = 1;
        protocol_analysis(xSerial1.ucData, xSerial1.usLen);
        memset(xSerial1.ucData, 0, xSerial1.usLen + 1);
        HAL_UART_Receive_DMA(&huart1, xSerial1.ucData, UART1_MAX_LEN);
    }
}


void UART3_IDLE_Callback(UART_HandleTypeDef *huart)
{
    if( __HAL_UART_GET_FLAG(&huart3, UART_FLAG_IDLE) != RESET)
    {
        __HAL_UART_CLEAR_IDLEFLAG(&huart3);
        uint32_t temp = huart3.Instance->SR;
        temp = huart3.Instance->DR;
        HAL_UART_DMAStop(&huart3);
        temp  = hdma_usart3_rx.Instance->CNDTR;
        xSerial3.usLen =  UART3_MAX_LEN - temp;
        uart3_analysis_flag = 1;
        memset(xSerial3.ucData, 0, xSerial3.usLen + 1);
        HAL_UART_Receive_DMA(&huart3, xSerial3.ucData, UART3_MAX_LEN);
    }
}
