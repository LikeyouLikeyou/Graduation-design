#ifndef _PWM_H_
#define _PWM_H_

#include "stm32f10x.h"

void PWM_Initialization(void);
void TIM3_Init(u16 arr,u16 psc);
void PWM_Init(void);
void PWM_Output(u16 Compare2);
#endif
