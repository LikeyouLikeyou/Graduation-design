#include "HX711.h"


/*
 * HX711和单片机连线是： PA6接SCK  PA7接DT  单片机3.3接模块的VCC  单片机GND接模块的GND
 */

unsigned long	Weight_Maopi;
unsigned long	HX711_Buffer;
unsigned long	Weight_Shiwu;
u8		Flag_Error = 0;

void InitioHX711( void )
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE ); /* 使能PB,PE端口时钟 */


    GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_Out_PP;     /* 推挽输出 */
    GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;     /* IO口速度为50MHz */

    /* PA7  DOUT */
    GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IPU;        /* 设置成上拉输入 */
    GPIO_Init( GPIOA, &GPIO_InitStructure );                /* 初始化GPIOE7 */

    /* PA6  SCK */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;               /* LED1-->PE.6 端口配置, 推挽输出 */
    GPIO_Init( GPIOA, &GPIO_InitStructure );                /* 推挽输出 ，IO口速度为50MHz */
    GPIO_ResetBits( GPIOA, GPIO_Pin_6 );                    /* PE.2 输出低 */
}


/* 3.3V供电                 2.2接SCK  2.3接DT */
unsigned long HX711_Read( void )
{
    unsigned long	Count;
    unsigned char	i;
    HX711SCK	= 0;                    /* SCL=0;使能AD（PD_SCL 置低） */
    Count		= 0;
    while ( HX711DT );
    /* AD转换未结束则等待，否则开始读取 */
    for ( i = 0; i < 24; i++ )
    {
        HX711SCK	= 1;            /* SCL = 1; PD_SCL 置高（发送脉冲） */
        Count		= Count << 1;   /*下降沿来时变量Count左移一位，右侧补零 */
        delay_us( 1 );
        HX711SCK = 0;                   /* SCL=0; PD_SCL 置低 */
        if ( HX711DT )
            Count++;                /* if(SDA) Count++; */
        delay_us( 1 );
    }
    HX711SCK	= 1;                    /* SCL=1; */
    Count		= Count ^ 0x800000;     /* 第25个脉冲下降沿来时，转换数据 */
    delay_us( 1 );
    HX711SCK = 0;                           /* SCL=0; */
    return(Count);
}


/*
 * ****************************************************
 * 获取毛皮重量
 * ****************************************************
 */
void Get_Maopi( void )
{
    Weight_Maopi = HX711_Read();
}


/*
 * ****************************************************
 * 称重
 * ****************************************************
 */
unsigned long Get_Weight( void )
{
    HX711_Buffer = HX711_Read();
    if ( HX711_Buffer > Weight_Maopi )
    {
        Weight_Shiwu	= HX711_Buffer;
        Weight_Shiwu	= Weight_Shiwu - Weight_Maopi;                          /* 获取实物的AD采样数值。 */

        Weight_Shiwu = (unsigned long) ( (float) Weight_Shiwu / GapValue);      /* 计算实物的实际重量 */
 
			
			 return (Weight_Shiwu / 1000); /* 单位是g */
        /*
         * 因为不同的传感器特性曲线不一样，因此，每一个传感器需要矫正这里的GapValue这个除数。
         * 当发现测试出来的重量偏大时，增加该数值。
         * 如果测试出来的重量偏小时，减小改数值。
         * 该数值一般在4.0-5.0之间。因传感器不同而定。
         * +0.05是为了四舍五入百分位
         */
    }
		return 0;
		
}

