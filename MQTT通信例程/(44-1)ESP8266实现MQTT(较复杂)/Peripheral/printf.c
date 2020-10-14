#include "printf.h"

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

/*
 * 功能：串口1初始化
 * 参数：Baud
 * 解释：串口波特率
 */

void USART_Initialization(u32 Baud)
{

#if RECEIVE_INTERRUPT
	NVIC_InitTypeDef NVIC_InitStruct;   //声明结构体变量,用于嵌套向量中断控制寄存器初始化
#endif
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA,ENABLE);
	
    //USART1_TX   GPIOA.9
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;  //复用推挽输出,被用作第二功能时
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct);
	
    //USART1_RX	  GPIOA.10
	//由于CPU复位后，GPIO缺省都是浮空输入模式，因此下面这个步骤不是必须的
	//但是，我还是建议加上便于阅读，并且防止其它地方修改了这个口线的设置参数
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;  //浮空输入,IO的电平是不确定的
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
    GPIO_Init(GPIOA,&GPIO_InitStruct);
	
#if RECEIVE_INTERRUPT
	/*串口1接收中断配置*/
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;  //指定中断请求通道
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;    //使能指定的中断请求通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2; //配置2位抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;   //配置2位响应优先级
	NVIC_Init(&NVIC_InitStruct); //初始化外设嵌套向量中断控制寄存器
#endif

    /*串口配置*/
    USART_InitStruct.USART_BaudRate=Baud;                 //波特率
    USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //无硬件流
    USART_InitStruct.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;  //输入输出模式
    USART_InitStruct.USART_Parity=USART_Parity_No;           //无奇偶校验
    USART_InitStruct.USART_StopBits=USART_StopBits_1;        //一位停止位
    USART_InitStruct.USART_WordLength=USART_WordLength_8b;  //数据长度为8位
    USART_Init(USART1,&USART_InitStruct);

    USART_Cmd(USART1,ENABLE);                            //使能串口1
		
	//CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
	//如下语句解决第1个字节无法正确发送出去的问题：
	//清发送完成标志，Transmission Complete flag 
    USART_ClearFlag(USART1,USART_FLAG_TC);               //清除发送完成标志位

#if RECEIVE_INTERRUPT
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);         //串口1接收中断使能
#endif
}


#if RECEIVE_INTERRUPT

/*串口1接收中断*/
void USART1_IRQHandler()  //中断服务函数,此函数在startup_stm32f10x_hd.s里(翻译为中断请求管理者)
{
	u8 receiveDat;
	if (USART_GetITStatus(USART1, USART_IT_RXNE))  //如果发生接收中断
	{
		receiveDat = USART_ReceiveData(USART1); //通过外设USRAT1接收数据给receiveDat
		USART_SendData(USART1, receiveDat);  //通过外设USRAT1发送数据receiveDat给PC
	}
}

#endif

