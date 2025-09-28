//https://item.taobao.com/item.htm?id=717251001647
#include "common.h"

extern uint32_t ADC_BUF[10];

uint16_t vol_value[10]={0};//mV

uint8_t send_data[100] = {0};
uint8_t scott_data[22] = {0};

void send_mode1()
{
	printf("<v>:%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f\n",\
	(float)ADC_BUF[0] * (3.3 / 4096),\
	(float)ADC_BUF[1] * (3.3 / 4096),\
	(float)ADC_BUF[2] * (3.3 / 4096),\
	(float)ADC_BUF[3] * (3.3 / 4096),\
	(float)ADC_BUF[4] * (3.3 / 4096),\
	(float)ADC_BUF[5] * (3.3 / 4096),\
	(float)ADC_BUF[6] * (3.3 / 4096),\
	(float)ADC_BUF[7] * (3.3 / 4096),\
	(float)ADC_BUF[8] * (3.3 / 4096),\
	(float)ADC_BUF[9] * (3.3 / 4096)\
	);
}
/******************************Output ten ADC sampling values*********************************************/

void send_mode2()
{
    printf("CH0:%04d  %.3fV\n", ADC_BUF[0], (float)ADC_BUF[0] * (3.3 / 4096));
    printf("CH1:%04d  %.3fV\n", ADC_BUF[1], (float)ADC_BUF[1] * (3.3 / 4096));
    printf("CH2:%04d  %.3fV\n", ADC_BUF[2], (float)ADC_BUF[2] * (3.3 / 4096));
    printf("CH3:%04d  %.3fV\n", ADC_BUF[3], (float)ADC_BUF[3] * (3.3 / 4096));
    printf("CH4:%04d  %.3fV\n", ADC_BUF[4], (float)ADC_BUF[4] * (3.3 / 4096));
    printf("CH5:%04d  %.3fV\n", ADC_BUF[5], (float)ADC_BUF[5] * (3.3 / 4096));
    printf("CH6:%04d  %.3fV\n", ADC_BUF[6], (float)ADC_BUF[6] * (3.3 / 4096));
    printf("CH7:%04d  %.3fV\n", ADC_BUF[7], (float)ADC_BUF[7] * (3.3 / 4096));
    printf("CH8:%04d  %.3fV\n", ADC_BUF[8], (float)ADC_BUF[8] * (3.3 / 4096));
    printf("CH9:%04d  %.3fV\n", ADC_BUF[9], (float)ADC_BUF[9] * (3.3 / 4096));
}
/******************************Output single channel ADC sampling value*************************************/
void send_mode1_ch(uint8_t ch)
{
	printf("<%d>:%.3f\n",ch,(float)ADC_BUF[ch] * (3.3 / 4096));
}
/******************************Output single channel ADC sampling value*************************************/
void send_mode2_ch(uint8_t ch)
{
	printf("CH%d:%d  %.3fV\n",ch, ADC_BUF[ch], (float)ADC_BUF[ch] * (3.3 / 4096));
}



