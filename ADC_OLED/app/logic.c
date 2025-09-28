//https://item.taobao.com/item.htm?id=718212632480

#include "common.h"

extern uint32_t ADC_BUF[30];
uint16_t adc_ch_average[3] = {0};
#define N 11
char median_filter()//中位滤波
{
    char value_buf[N];
    char count, i, j, temp;

    for(count = 0; count < N; count++) 
    {
        value_buf[count] = ADC_BUF[0];
    }

    for(j = 0; j < (N - 1); j++)
    {
        for(i = 0; i < (N - j); i++)
        {
            if(value_buf[i] > value_buf[i + 1])
            {
                temp = value_buf[i];
                value_buf[i] = value_buf[i + 1];
                value_buf[i + 1] = temp;
            }
        }
    }

    return value_buf[(N - 1) / 2];
}

void DMA_IRQ_Callback()
{
    uint16_t adc_ch_temp[3] = {0};
    HAL_ADC_Stop_DMA(&hadc1);

    for(int j = 0; j < 3; j++)
    {
        for(int i = 0; i < 30; i = i + 3)
        {
            adc_ch_temp[j] += ADC_BUF[i+j];
        }

        adc_ch_average[j] = adc_ch_temp[j] / 10;
    }

    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)ADC_BUF, 60);
}

void show_title_intensity(uint8_t ch)
{
		uint16_t x_pos_offset=20;
		uint16_t xspace_pos_offset=20;
		uint16_t y_pos_offset=1;
		OLED_ShowCHinese(x_pos_offset,y_pos_offset,0);
		OLED_ShowCHinese(x_pos_offset+xspace_pos_offset,y_pos_offset,1);
		switch(ch)
		{
			case 1:
				OLED_ShowString(x_pos_offset+xspace_pos_offset+20, y_pos_offset, (uint8_t *)"1", 16);
				break;
			case 2:
				OLED_ShowString(x_pos_offset+xspace_pos_offset+20, y_pos_offset, (uint8_t *)"2", 16);
				break;
			case 3:
				OLED_ShowString(x_pos_offset+xspace_pos_offset+20, y_pos_offset, (uint8_t *)"3", 16);
				break;
			default:
				OLED_ShowString(x_pos_offset+xspace_pos_offset+20, y_pos_offset, (uint8_t *)"1", 16);
				break;
		}		
		OLED_ShowCHinese(x_pos_offset+xspace_pos_offset*2+10,y_pos_offset,2);
		OLED_ShowCHinese(x_pos_offset+xspace_pos_offset*3+10,y_pos_offset,3);
}

void lcd_vol_adc_display(uint8_t ch_index)
{
		static char ch[20] = {0};
		if(ch_index<3)
		{
			if(!xMacInfo.show_once_ch_title)
			{
				show_title_intensity(ch_index+1);
				xMacInfo.show_once_ch_title=1;
			}
			snprintf(ch, 20, "VOL%d: %0.3fV",ch_index+1, (float)adc_ch_average[ch_index] * (3.3 / 4096) * 14 / 9);
			OLED_ShowString(15, 4, (uint8_t *)ch, 16);
		}
		else if(ch_index==3)
		{
			static char ch[20] = {0};
			snprintf(ch, 20, "VOL1: %0.3fV", (float)adc_ch_average[0] * (3.3 / 4096) * 14 / 9);
			OLED_ShowString(15, 0, (uint8_t *)ch, 16);
			snprintf(ch, 20, "VOL2: %0.3fV", (float)adc_ch_average[1] * (3.3 / 4096) * 14 / 9);
			OLED_ShowString(15, 3, (uint8_t *)ch, 16);
			snprintf(ch, 20, "VOL3: %0.3fV", (float)adc_ch_average[2] * (3.3 / 4096) * 14 / 9);
			OLED_ShowString(15, 6, (uint8_t *)ch, 16);
		}
}

//void Airplane()//hex协议，通道一
//{
//	uint8_t sendBuf[4];
//	sendBuf[0]=ADC_BUF[0]>>8;
//	sendBuf[1]=ADC_BUF[0];
//	sendBuf[2]=0xFF;
//	sendBuf[3]=0xFF;
//	HAL_UART_Transmit(&huart1, (uint8_t*)&sendBuf, 4, 10);
//}
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
        memset(xSerial3.ucData, 0, xSerial3.usLen + 1);
        HAL_UART_Receive_DMA(&huart3, xSerial3.ucData, UART3_MAX_LEN);
    }
}



