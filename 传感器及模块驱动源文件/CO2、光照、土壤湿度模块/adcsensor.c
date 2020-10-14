 #include "adcsensor.h"
 #include "delay.h"
		   
//��ʼ��ADC

float CO2_data,Soil_data,Light_data;           //����ֵ
uint16_t CO2_temp,Soil_temp,Light_temp;        //�м�
															   
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	//PB0��1 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_1|GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//PA7    ��Ϊģ��ͨ����������
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	ADC_DeInit(ADC1);  //��λADC1 

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;												//ADC����ģʽ:ADC1��ADC1�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;															//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;												//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;				//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;										//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 2;																		//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);																				//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

  
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
 
}		

//���ADCֵ
//ch:ͨ��ֵ 0~3
static u16 Get_Adc(u8 ch)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}

/*ch:ADCͨ����timesΪ��������*/
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
  * @Name   : ���CO2Ũ�Ⱥ���
  *
  * @Brief  : PA7
  *
  * @Input  : none
  *                      
  * @Output : none
  *
  * @Return : ʵ��CO2Ũ�Ȱٷֱ�ֵ
  *****************************************************************************
 */
float CO2_Concentration(void)
{
	 /*��ȡˮλ*/
	 CO2_temp=Get_Adc_Average(ADC_Channel_7,10);
	 CO2_data=(3.3-(CO2_temp/4096.0)*3.3)/3.3*100;     //ˮλ������ADCת��Ϊ�ٷ�ֵ
	 CO2_data=100.0-CO2_data;
	
	 return CO2_data;
}

/*
  *****************************************************************************
  * @Name   : �������ʪ�Ⱥ���
  *
  * @Brief  : PB0
  *
  * @Input  : none
  *                      
  * @Output : none
  *
  * @Return : ʵ������ʪ�Ȱٷֱ�ֵ
  *****************************************************************************
 */
float Soil_moisture(void)
{
	 /*��ȡˮλ*/
	 Soil_temp=Get_Adc_Average(ADC_Channel_8,10);
	 Soil_data=(3.3-(Soil_temp/4096.0)*3.3)/3.3*100;     //ˮλ������ADCת��Ϊ�ٷ�ֵ
	 Soil_data=100.0-Soil_data;
	
	 return Soil_data;
}

/*
  *****************************************************************************
  * @Name   : ��ù���ǿ�Ⱥ���
  *
  * @Brief  : �˿�PB1
  *
  * @Input  : none
  *                      
  * @Output : none
  *
  * @Return : ʵ�ʹ���ǿ�Ȱٷֱ�ֵ
  *****************************************************************************
 */
float Light_intensity(void)
{
	 /*��ȡˮλ*/
	 Light_temp=Get_Adc_Average(ADC_Channel_9,10);
	 Light_data=(3.3-(Light_temp/4096.0)*3.3)/3.3*100;     //ˮλ������ADCת��Ϊ�ٷ�ֵ
	 Light_data=100.0-Light_data;
	
	 return Light_data;
}

























