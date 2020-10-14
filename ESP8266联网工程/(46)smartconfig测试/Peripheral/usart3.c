#include "usart3.h"

u8 txbuf[256];
char rxbuf[256];
u8 temp;

u8 UsartReadFlage;

//����3�ж�����
static void Usart3_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //�����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
}

//����3���ú���
void Usart3_Configuration(u32 BAUD)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    /*����USART2��GPIOʱ��*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    /*GPIO����*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;    //TX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;    //RX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* UART2���� */
    USART_InitStructure.USART_BaudRate = BAUD;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART3, &USART_InitStructure);
    USART_Cmd(USART3, ENABLE);
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);

    Usart3_NVIC_Configuration();
}

//����3����һ���ֽ�
void Usart3_SendByte(u8 val)
{
    USART_SendData(USART3, val);
    while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);	//�ȴ��������
}
//����3����һ�����ݰ�
void Usart3_SendBuf(u8 *buf,u8 len)
{
    while(len--)	Usart3_SendByte(*buf++);
}

//����3����һ���ַ���
void Usart3_SendString(char *str)
{
    while(*str)	Usart3_SendByte(*str++);
}

/* ����3�жϷ����� */
void USART3_IRQHandler(void)
{
    static u8 rxlen = 0;

    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //�жϽ������ݼĴ����Ƿ�������
    {
			  UsartReadFlage=1;
        temp = USART3->DR;                                //���ｫ����3Ҳ����ESP8266���յ�������ͨ�����ڵ����ݽ��ռĴ����ó����ŵ�temp�м����Ȼ�������Ĵ���1��ӡ����
        USART1->DR = temp;                                //������������1��ӡWIFIģ����յ��Ļ�Ӧ����
        if(rxlen>=255) rxlen=0;
        rxbuf[rxlen++] = temp;
        rxlen%=sizeof(rxbuf);
    }

    if(USART_GetITStatus(USART3, USART_IT_IDLE))         //����3����������������ж�
    {
        temp = USART3->DR;
        temp = USART3->SR;
        rxlen = rxlen;
        rxlen=0;
    }
}
/*********************************************END OF FILE********************************************/
