//https://item.taobao.com/item.htm?id=717251001647
#include "common.h"

void delay5ms()
{
	unsigned char i, j, k;
	i = 2;
	j = 56;
	k = 66;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


#define FLASH_MACINFO_ADDR 0x0800FC00  // 指定的 Flash 地址

// 将 xMacInfo 存储到指定的 Flash 地址
HAL_StatusTypeDef save_xMacInfo_to_flash(void)
{
    HAL_StatusTypeDef status = HAL_OK;
    
    // 解锁 Flash
    HAL_FLASH_Unlock();
    
    // 擦除目标页
    FLASH_EraseInitTypeDef EraseInitStruct;
    uint32_t PageError = 0;
    
    EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.PageAddress = FLASH_MACINFO_ADDR;
    EraseInitStruct.NbPages = 1;
    
    status = HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);
    
    if (status == HAL_OK)
    {
        // 以 16 位为单位写入数据（F103 使用 16 位）
        uint16_t *data = (uint16_t*)&xMacInfo;
        for (int i = 0; i < sizeof(xMacInfo_t) / 2; i++)
        {
            status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, 
                                       FLASH_MACINFO_ADDR + i * 2, 
                                       data[i]);
						delay5ms();
            if (status != HAL_OK)
            {
                break;
            }
        }
    }
    
    // 锁定 Flash
    HAL_FLASH_Lock();
    
    return status;
}

// 从指定的 Flash 地址读取 xMacInfo
HAL_StatusTypeDef read_xMacInfo_from_flash(void)
{
    // 直接从 Flash 地址读取数据到 xMacInfo
    memcpy(&xMacInfo, (void*)FLASH_MACINFO_ADDR, sizeof(xMacInfo_t));
    // 可以添加一些校验逻辑，确保读取的数据有效
    if (xMacInfo.mode_index > 4 || 
        xMacInfo.select_m1ch > 9 || 
        xMacInfo.select_m2ch > 9)
    {
        // 如果数据无效，可以重置为默认值
				xMacInfo.mode_index=0x01;
				xMacInfo.select_m1ch=0x00;
				xMacInfo.select_m2ch=0x00;
				xMacInfo.baud=460800;
				xMacInfo.send_rate=50;
				//save_xMacInfo_to_flash();
    }
    return HAL_OK;
}
