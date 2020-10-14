#include "HX711.h"


/*
 * HX711�͵�Ƭ�������ǣ� PA6��SCK  PA7��DT  ��Ƭ��3.3��ģ���VCC  ��Ƭ��GND��ģ���GND
 */

unsigned long	Weight_Maopi;
unsigned long	HX711_Buffer;
unsigned long	Weight_Shiwu;
u8		Flag_Error = 0;

void InitioHX711( void )
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE ); /* ʹ��PB,PE�˿�ʱ�� */


    GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_Out_PP;     /* ������� */
    GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;     /* IO���ٶ�Ϊ50MHz */

    /* PA7  DOUT */
    GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IPU;        /* ���ó��������� */
    GPIO_Init( GPIOA, &GPIO_InitStructure );                /* ��ʼ��GPIOE7 */

    /* PA6  SCK */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;               /* LED1-->PE.6 �˿�����, ������� */
    GPIO_Init( GPIOA, &GPIO_InitStructure );                /* ������� ��IO���ٶ�Ϊ50MHz */
    GPIO_ResetBits( GPIOA, GPIO_Pin_6 );                    /* PE.2 ����� */
}


/* 3.3V����                 2.2��SCK  2.3��DT */
unsigned long HX711_Read( void )
{
    unsigned long	Count;
    unsigned char	i;
    HX711SCK	= 0;                    /* SCL=0;ʹ��AD��PD_SCL �õͣ� */
    Count		= 0;
    while ( HX711DT );
    /* ADת��δ������ȴ�������ʼ��ȡ */
    for ( i = 0; i < 24; i++ )
    {
        HX711SCK	= 1;            /* SCL = 1; PD_SCL �øߣ��������壩 */
        Count		= Count << 1;   /*�½�����ʱ����Count����һλ���Ҳಹ�� */
        delay_us( 1 );
        HX711SCK = 0;                   /* SCL=0; PD_SCL �õ� */
        if ( HX711DT )
            Count++;                /* if(SDA) Count++; */
        delay_us( 1 );
    }
    HX711SCK	= 1;                    /* SCL=1; */
    Count		= Count ^ 0x800000;     /* ��25�������½�����ʱ��ת������ */
    delay_us( 1 );
    HX711SCK = 0;                           /* SCL=0; */
    return(Count);
}


/*
 * ****************************************************
 * ��ȡëƤ����
 * ****************************************************
 */
void Get_Maopi( void )
{
    Weight_Maopi = HX711_Read();
}


/*
 * ****************************************************
 * ����
 * ****************************************************
 */
unsigned long Get_Weight( void )
{
    HX711_Buffer = HX711_Read();
    if ( HX711_Buffer > Weight_Maopi )
    {
        Weight_Shiwu	= HX711_Buffer;
        Weight_Shiwu	= Weight_Shiwu - Weight_Maopi;                          /* ��ȡʵ���AD������ֵ�� */

        Weight_Shiwu = (unsigned long) ( (float) Weight_Shiwu / GapValue);      /* ����ʵ���ʵ������ */
 
			
			 return (Weight_Shiwu / 1000); /* ��λ��g */
        /*
         * ��Ϊ��ͬ�Ĵ������������߲�һ������ˣ�ÿһ����������Ҫ���������GapValue���������
         * �����ֲ��Գ���������ƫ��ʱ�����Ӹ���ֵ��
         * ������Գ���������ƫСʱ����С����ֵ��
         * ����ֵһ����4.0-5.0֮�䡣�򴫸�����ͬ������
         * +0.05��Ϊ����������ٷ�λ
         */
    }
		return 0;
		
}

