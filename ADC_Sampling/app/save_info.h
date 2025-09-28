#ifndef __SAVE_INFO_H
#define	__SAVE_INFO_H

#include "stm32f1xx_hal.h"

HAL_StatusTypeDef save_xMacInfo_to_flash(void);
HAL_StatusTypeDef read_xMacInfo_from_flash(void);

#endif
