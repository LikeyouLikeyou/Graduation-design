#include "matrix.h"



/*    接线说明  */
/*
      PB12——C1
			PB13——C2
			PB14——C3
			PB15——C4

			PB5——R1
			PB6——R2
			PB7——R3
			PB8——R4
*/

uint8_t relayms=50;

/*
  *****************************************************************************
  * @Name   : 矩阵按键GPIO初始化函数
  *
  * @Brief  :
 	*           无按键被按下时；PB5 - PB8 为0，为低电平状态
  *           有按键被按下时：PA5 - PA2 相应的引脚显示为高电平
  *
  * @Input  : none
  *
  * @Output : none
  *
  * @Return : none
  *****************************************************************************
 */
void Matrix_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruction;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    /* 列 */
    GPIO_InitStruction.GPIO_Mode=GPIO_Mode_Out_PP;                                //推挽输出
    GPIO_InitStruction.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;      //PB—12、13、14、15  C1、C2、C3、C4
    GPIO_InitStruction.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStruction);

    /* 行 */
    GPIO_InitStruction.GPIO_Mode=GPIO_Mode_IPD;                                   //下拉输入
    GPIO_InitStruction.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;      //PB—5、6、7、8  R1、R2、R3、R4
    GPIO_InitStruction.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStruction);

}

/**************************************************************
函数名称: Value44Key(void)
函数功能: 判定4X4矩阵按键是否按下
输入参数: 无


返 回 值: 矩阵按键键值
备    注: 无
**************************************************************/
int Value44Key(void)                                          //定义矩阵键盘的返回值，返回值对应相关功能，
{
    int KeyValue = 0;                                         //KeyValue是最后返回的按键数值
    GPIO_Write(GPIOB,((GPIOB->ODR & 0x0FFF )| 0xF000));       //先让PB12 - PB15全部输出高

    if((GPIOB->IDR & 0x01E0) == 0x0000)                       //先设置 PB5 - PB8 为0，如果没有按键按下，返回值为-1
    {
        return -1;
    }
    else                                                     //有按键按下
    {
        delay_ms(10);                                         //延时10ms去抖动
        if((GPIOB->IDR & 0x01E0) == 0x0000)                  //如果延时5ms后 PB5 - PB8 又全为0， 则刚刚是抖动产生的
        {
            return -1;                                       //所以还是返回 -1
        }
        else
        {
            GPIO_Write(GPIOB, (GPIOB->ODR & 0x0FFF )| 0x8000 );       //要让 PB12 - PB15 输出二进制的 0001
            switch(GPIOB->IDR & 0x01E0)                               //对应的 PB5 - PB8 的值进行判断，输出不同的按键值
            {
            case 0x0100:
                KeyValue = 15;
                break;

            case 0x0080:
                KeyValue = 11;
                break;

            case 0x0040:
                KeyValue = 7;
                break;

            case 0x0020:
                KeyValue = 3;
                break;
            }

            GPIO_Write(GPIOB, (GPIOB->ODR & 0x0FFF )| 0x4000 );        //要让 PB12 - PB15 输出二进制的 0010
            switch(GPIOB->IDR & 0x01E0)                                //对应的 PB5 - PB8 的值进行判断，输出不同的按键值
            {
            case 0x0100:
                KeyValue = 14;
                break;

            case 0x0080:
                KeyValue = 10;
                break;

            case 0x0040:
                KeyValue = 6;
                break;

            case 0x0020:
                KeyValue = 2;
                break;
            }

            GPIO_Write(GPIOB, (GPIOB->ODR & 0x0FFF )| 0x2000 );      //要让 PB12 - PB15 输出二进制的 0100
            switch(GPIOB->IDR & 0x01E0)                              //对应的 PB5 - PB8 的值进行判断，输出不同的按键值
            {
            case 0x0100:
                KeyValue = 13;
                break;

            case 0x0080:
                KeyValue = 9;
                break;

            case 0x0040:
                KeyValue = 5;
                break;

            case 0x0020:
                KeyValue = 1;
                break;
            }

            GPIO_Write(GPIOB, (GPIOB->ODR & 0x0FFF )| 0x1000 );      //要让 PB12 - PB15 输出二进制的 1000
            switch(GPIOB->IDR & 0x01E0)                              //对应的 PB5 - PB8 的值进行判断，输出不同的按键值
            {
            case 0x0100:
                KeyValue = 12;
                break;

            case 0x0080:
                KeyValue = 8;
                break;

            case 0x0040:
                KeyValue = 4;
                break;

            case 0x0020:
                KeyValue = 0;
                break;
            }

            while(((GPIOB->IDR & 0x01E0)==0x0000) && (relayms--))      //按键松手检测
            {
                delay_ms(1);
            }

            return KeyValue;
        }
    }
}





