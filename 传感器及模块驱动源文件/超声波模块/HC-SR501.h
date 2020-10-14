#ifndef __HR_SR501_H_
#define __HR_SR501_H_

#include "stm32f10x.h"

#define HCSR501 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)    //读取人体红外的值，高电平则表示有人进入红外区域

void HCSR501_Initialization(void);

#endif
