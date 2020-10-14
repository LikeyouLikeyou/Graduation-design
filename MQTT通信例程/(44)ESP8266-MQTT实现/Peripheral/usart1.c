#include "usart1.h"

/*printf重定向*/
int fputc(int ch,FILE *p)
{
    USART_SendData(USART1,(u8)ch);                             //强制转换为u8类型也就是一个字节
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);  //如果发送完成

    return ch;
}

/*scanf重定向*/
int fgetc(FILE *stream)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==RESET){};    //等待接收数据寄存器非空标志位
	
	 return (int)USART_ReceiveData(USART1);                         //返回接收到的数据
}

//串口1配置函数
void Usart1_Configuration(u32 BAUD)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    //第一步：初始化时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

    //第二步：初始化GPIO
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10

    //第三步：初始化串口参数
    USART_InitStructure.USART_BaudRate = BAUD;//串口波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
    USART_Init(USART1, &USART_InitStructure); //初始化串口1


    //第六步：使能串口
    USART_Cmd(USART1, ENABLE);                    //使能串口1
    USART_ClearFlag(USART1, USART_FLAG_TC);       //清空发送完成标志
}

//串口1发送一个字节
void Usart1_SendByte(u8 val)
{
    USART_SendData(USART1, val);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);	//等待发送完成
}
//串口1发送一个数据包
void Usart1_SendBuf(u8 *buf,u8 len)
{
    while(len--)	Usart1_SendByte(*buf++);
}

//串口1发送一个字符串
void Usart1_SendString(char *str)
{
    while(*str)	Usart1_SendByte(*str++);
}




/*********************************************END OF FILE********************************************/
