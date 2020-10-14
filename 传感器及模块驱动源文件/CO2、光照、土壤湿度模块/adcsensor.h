#ifndef __ADCSENSOR_H
#define __ADCSENSOR_H	

#include "stm32f10x.h"


void Adc_Init(void);                    //ADC初始化

float CO2_Concentration(void);           //CO2浓度
float Soil_moisture(void);               //土壤湿度
float Light_intensity(void);             //光照强度

#endif 
