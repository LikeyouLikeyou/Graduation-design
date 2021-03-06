#include "usart2.h"

u8 txbuf[256];
u8 rxbuf[256];
u8 temp;

//串口2中断配置
static void Usart2_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //先占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //从优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
}

//串口2配置函数
void Usart2_Configuration(u32 BAUD)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    /*配置USART2和GPIO时钟*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    /*GPIO配置*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;    //TX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;    //RX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* UART2配置 */
    USART_InitStructure.USART_BaudRate = BAUD;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART2, &USART_InitStructure);
    USART_Cmd(USART2, ENABLE);
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);

    Usart2_NVIC_Configuration();
}

//串口2发送一个字节
void Usart2_SendByte(u8 val)
{
    USART_SendData(USART2, val);
    while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);	//等待发送完成
}
//串口2发送一个数据包
void Usart2_SendBuf(u8 *buf,u8 len)
{
    while(len--)	Usart2_SendByte(*buf++);
}

//串口2发送一个字符串
void Usart2_SendString(char *str)
{
    while(*str)	Usart2_SendByte(*str++);
}

/* 串口2中断服务函数 */
void USART2_IRQHandler(void)
{
    static u8 rxlen = 0;

    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //判断接收数据寄存器是否有数据
    {
        temp = USART2->DR;                                //这里将串口2也就是ESP8266接收到的数据通过串口的数据接收寄存器拿出来放到temp中间变量然后给下面的串口1打印出来
        USART1->DR = temp;                                //这里用作串口1打印WIFI模块接收到的回应数据
        if(rxlen>=255) rxlen=0;
        rxbuf[rxlen++] = temp;
        rxlen%=sizeof(rxbuf);
    }

    if(USART_GetITStatus(USART2, USART_IT_IDLE))         //串口2如果产生空闲总线中断
    {
        temp = USART2->DR;
        temp = USART2->SR;
        rxlen = rxlen;
        rxlen=0;
    }
}
/*********************************************END OF FILE********************************************/
