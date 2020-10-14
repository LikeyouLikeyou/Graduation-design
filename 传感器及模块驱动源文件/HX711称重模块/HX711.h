#ifndef __HX711_H_
#define __HX711_H_

#include "stm32f10x.h"
#include "delay.h"
#include "BitOperation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 这个值需要修正 根据实际 */
#define GapValue	0.38755
#define HX711DT		GPIO_ReadInputDataBit( GPIOA, GPIO_Pin_7 )
#define HX711SCK	PAout( 6 )

void InitioHX711( void );
unsigned long HX711_Read( void );
void Get_Maopi( void );
unsigned long Get_Weight( void );

#endif
