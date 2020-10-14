#ifndef __RELAY_H_
#define __RELAY_H_

#include "stm32f10x.h"

/* עˮ */
#define OPEN    GPIO_SetBits(GPIOB,GPIO_Pin_13)
#define CLOSE   GPIO_ResetBits(GPIOB,GPIO_Pin_13)


void GPIO_Initialization(void);



#endif
