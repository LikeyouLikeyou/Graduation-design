#include "usart2.h"

u8 txbuf[256];
u8 rxbuf[256];
u8 temp;

//����2�ж�����
static void Usart2_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //�����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
}

//����2���ú���
void Usart2_Configuration(u32 BAUD)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    /*����USART2��GPIOʱ��*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    /*GPIO����*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;    //TX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;    //RX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* UART2���� */
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

//����2����һ���ֽ�
void Usart2_SendByte(u8 val)
{
    USART_SendData(USART2, val);
    while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);	//�ȴ��������
}
//����2����һ�����ݰ�
void Usart2_SendBuf(u8 *buf,u8 len)
{
    while(len--)	Usart2_SendByte(*buf++);
}

//����2����һ���ַ���
void Usart2_SendString(char *str)
{
    while(*str)	Usart2_SendByte(*str++);
}

/* ����2�жϷ����� */
void USART2_IRQHandler(void)
{
    static u8 rxlen = 0;

    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //�жϽ������ݼĴ����Ƿ�������
    {
        temp = USART2->DR;                                //���ｫ����2Ҳ����ESP8266���յ�������ͨ�����ڵ����ݽ��ռĴ����ó����ŵ�temp�м����Ȼ�������Ĵ���1��ӡ����
        USART1->DR = temp;                                //������������1��ӡWIFIģ����յ��Ļ�Ӧ����
        if(rxlen>=255) rxlen=0;
        rxbuf[rxlen++] = temp;
        rxlen%=sizeof(rxbuf);
    }

    if(USART_GetITStatus(USART2, USART_IT_IDLE))         //����2����������������ж�
    {
        temp = USART2->DR;
        temp = USART2->SR;
        rxlen = rxlen;
        rxlen=0;
    }
}
/*********************************************END OF FILE********************************************/
