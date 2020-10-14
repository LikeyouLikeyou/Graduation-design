 #include "adcsensor.h"
 #include "delay.h"
		   
//初始化ADC

float CO2_data,Soil_data,Light_data;           //最终值
uint16_t CO2_temp,Soil_temp,Light_temp;        //中间
															   
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1	, ENABLE );	  //使能ADC1通道时钟
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	//PB0、1 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_1|GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//PA7    作为模拟通道输入引脚
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	ADC_DeInit(ADC1);  //复位ADC1 

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;												//ADC工作模式:ADC1和ADC1工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;															//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;												//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;				//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;										//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 2;																		//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);																				//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

  
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC1);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
 
}		

//获得ADC值
//ch:通道值 0~3
static u16 Get_Adc(u8 ch)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}

/*ch:ADC通道，times为采样次数*/
static u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
} 	 


/*
  *****************************************************************************
  * @Name   : 获得CO2浓度函数
  *
  * @Brief  : PA7
  *
  * @Input  : none
  *                      
  * @Output : none
  *
  * @Return : 实际CO2浓度百分比值
  *****************************************************************************
 */
float CO2_Concentration(void)
{
	 /*获取水位*/
	 CO2_temp=Get_Adc_Average(ADC_Channel_7,10);
	 CO2_data=(3.3-(CO2_temp/4096.0)*3.3)/3.3*100;     //水位传感器ADC转换为百分值
	 CO2_data=100.0-CO2_data;
	
	 return CO2_data;
}

/*
  *****************************************************************************
  * @Name   : 获得土壤湿度函数
  *
  * @Brief  : PB0
  *
  * @Input  : none
  *                      
  * @Output : none
  *
  * @Return : 实际土壤湿度百分比值
  *****************************************************************************
 */
float Soil_moisture(void)
{
	 /*获取水位*/
	 Soil_temp=Get_Adc_Average(ADC_Channel_8,10);
	 Soil_data=(3.3-(Soil_temp/4096.0)*3.3)/3.3*100;     //水位传感器ADC转换为百分值
	 Soil_data=100.0-Soil_data;
	
	 return Soil_data;
}

/*
  *****************************************************************************
  * @Name   : 获得光照强度函数
  *
  * @Brief  : 端口PB1
  *
  * @Input  : none
  *                      
  * @Output : none
  *
  * @Return : 实际光照强度百分比值
  *****************************************************************************
 */
float Light_intensity(void)
{
	 /*获取水位*/
	 Light_temp=Get_Adc_Average(ADC_Channel_9,10);
	 Light_data=(3.3-(Light_temp/4096.0)*3.3)/3.3*100;     //水位传感器ADC转换为百分值
	 Light_data=100.0-Light_data;
	
	 return Light_data;
}

























