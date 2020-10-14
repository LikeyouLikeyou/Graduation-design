#ifndef __BEER_H_
#define __BEER_H_

#include "stm32f10x.h"

#define BEER_ON   GPIO_SetBits(GPIOA,GPIO_Pin_6)
#define BEER_OFF  GPIO_ResetBits(GPIOA,GPIO_Pin_6)


void Beer_Init(void);    //PA6

#endif
