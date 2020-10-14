#include "MQ-2.h"
#include "delay.h"

//��ʼ��ADC
/* �������ǳ�ʼ������ADC_IN8��ADC_IN9��Ӧ����PB0��PB1 */
float MQ;
uint16_t MQ_temp;

void  Adc_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |RCC_APB2Periph_ADC1, ENABLE );	  //ʹ��ADC1ͨ��ʱ��

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

    //PB1 ��Ϊģ��ͨ����������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    ADC_DeInit(ADC1);  //��λADC1

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC1�����ڶ���ģʽ
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
    ADC_InitStructure.ADC_NbrOfChannel = 2;	//˳����й���ת����ADCͨ������Ŀ
    ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���


    ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1

    ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼

    while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����

    ADC_StartCalibration(ADC1);	 //����ADУ׼

    while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����

}
//���ADCֵ
//ch:ͨ��ֵ 0~9
static u16 Get_Adc(u8 ch)
{
    //����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������

    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

    return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}

static u16 Get_Adc_Average(u8 ch,u8 times)
{
    u32 temp_val=0;
    u8 t;
    for(t=0; t<times; t++)
    {
        temp_val+=Get_Adc(ch);
        delay_ms(5);
    }
    return temp_val/=times;//�õ�ƽ��ֵ
}

/*
  *****************************************************************************
  * @Name   : ���MQ-2Ũ�Ⱥ���
  *
  * @Brief  : PB1
  *
  * @Input  : none
  *
  * @Output : none
  *
  * @Return : ʵ��MQ-2Ũ�Ȱٷֱ�ֵ
  *****************************************************************************
 */
float Get_MQ_2(void)
{
    /*��ȡ�к�����*/
    MQ_temp=Get_Adc_Average(ADC_Channel_9,10);
    MQ=(3.3-(MQ_temp/4096.0)*3.3)/3.3*100;     //ˮλ������ADCת��Ϊ�ٷ�ֵ
	
    return MQ;
}

