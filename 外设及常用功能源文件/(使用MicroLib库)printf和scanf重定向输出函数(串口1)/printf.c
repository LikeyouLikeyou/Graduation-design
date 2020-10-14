#include "printf.h"

/*printf�ض���*/
int fputc(int ch,FILE *p)
{
    USART_SendData(USART1,(u8)ch);                             //ǿ��ת��Ϊu8����Ҳ����һ���ֽ�
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);  //����������

    return ch;
}

/*scanf�ض���*/
int fgetc(FILE *stream)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==RESET){};    //�ȴ��������ݼĴ����ǿձ�־λ
	
	 return (int)USART_ReceiveData(USART1);                         //���ؽ��յ�������
}

/*
 * ���ܣ�����1��ʼ��
 * ������Baud
 * ���ͣ����ڲ�����
 */

void USART_Initialization(u32 Baud)
{

#if RECEIVE_INTERRUPT
	NVIC_InitTypeDef NVIC_InitStruct;   //�����ṹ�����,����Ƕ�������жϿ��ƼĴ�����ʼ��
#endif
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA,ENABLE);
	
    //USART1_TX   GPIOA.9
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;  //�����������,�������ڶ�����ʱ
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct);
	
    //USART1_RX	  GPIOA.10
	//����CPU��λ��GPIOȱʡ���Ǹ�������ģʽ���������������費�Ǳ����
	//���ǣ��һ��ǽ�����ϱ����Ķ������ҷ�ֹ�����ط��޸���������ߵ����ò���
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;  //��������,IO�ĵ�ƽ�ǲ�ȷ����
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
    GPIO_Init(GPIOA,&GPIO_InitStruct);
	
#if RECEIVE_INTERRUPT
	/*����1�����ж�����*/
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;  //ָ���ж�����ͨ��
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;    //ʹ��ָ�����ж�����ͨ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2; //����2λ��ռ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;   //����2λ��Ӧ���ȼ�
	NVIC_Init(&NVIC_InitStruct); //��ʼ������Ƕ�������жϿ��ƼĴ���
#endif

    /*��������*/
    USART_InitStruct.USART_BaudRate=Baud;                 //������
    USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None; //��Ӳ����
    USART_InitStruct.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;  //�������ģʽ
    USART_InitStruct.USART_Parity=USART_Parity_No;           //����żУ��
    USART_InitStruct.USART_StopBits=USART_StopBits_1;        //һλֹͣλ
    USART_InitStruct.USART_WordLength=USART_WordLength_8b;  //���ݳ���Ϊ8λ
    USART_Init(USART1,&USART_InitStruct);

    USART_Cmd(USART1,ENABLE);                            //ʹ�ܴ���1
		
	//CPU��Сȱ�ݣ��������úã����ֱ��Send�����1���ֽڷ��Ͳ���ȥ
	//�����������1���ֽ��޷���ȷ���ͳ�ȥ�����⣺
	//�巢����ɱ�־��Transmission Complete flag 
    USART_ClearFlag(USART1,USART_FLAG_TC);               //���������ɱ�־λ

#if RECEIVE_INTERRUPT
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);         //����1�����ж�ʹ��
#endif
}


#if RECEIVE_INTERRUPT

/*����1�����ж�*/
void USART1_IRQHandler()  //�жϷ�����,�˺�����startup_stm32f10x_hd.s��(����Ϊ�ж����������)
{
	u8 receiveDat;
	if (USART_GetITStatus(USART1, USART_IT_RXNE))  //������������ж�
	{
		receiveDat = USART_ReceiveData(USART1); //ͨ������USRAT1�������ݸ�receiveDat
		USART_SendData(USART1, receiveDat);  //ͨ������USRAT1��������receiveDat��PC
	}
}

#endif

