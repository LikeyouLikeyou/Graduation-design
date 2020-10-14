#ifndef __WATERPUMP_H_
#define __WATERPUMP_H_

#include "stm32f10x.h"

/* в╒к╝ */
#define IN_ON    GPIO_SetBits(GPIOB,GPIO_Pin_5)
#define IN_OFF   GPIO_ResetBits(GPIOB,GPIO_Pin_5)

/* еек╝ */
#define OUT_ON   GPIO_SetBits(GPIOB,GPIO_Pin_6)
#define OUT_OFF  GPIO_ResetBits(GPIOB,GPIO_Pin_6)

void GPIO_Initialization(void);



#endif
