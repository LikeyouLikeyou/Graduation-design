#include "spi.h"

/*
 * @brief  Ӳ��SPI2��ʼ������
 *
 * @param  None
 *         
 * @retval None
 *
 */
void SPI_Configuration()
{
  GPIO_InitTypeDef GPIO_InitStruction;
	SPI_InitTypeDef SPI_InitStruction;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	
	GPIO_InitStruction.GPIO_Mode=GPIO_Mode_AF_PP;                        //�����������
	GPIO_InitStruction.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStruction.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruction);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);             //Ĭ��Ϊ�ߵ�ƽ
	
	SPI_InitStruction.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_256;    //������Ԥ��ƵֵΪ 256       APB1Ĭ�����Ϊ72M  ���ﻹҪ�ڴ˻�����256��Ƶ
	SPI_InitStruction.SPI_CPHA=SPI_CPHA_1Edge;                            //������ʱ�ӵĵ�һ�����زɼ�  
	SPI_InitStruction.SPI_CPOL=SPI_CPOL_Low;                              //ʱ������ʱΪ��
	SPI_InitStruction.SPI_CRCPolynomial=7;                                //CRCֵ����Ķ���ʽ
	SPI_InitStruction.SPI_DataSize=SPI_DataSize_8b;                       //SPI���ͽ���8λ֡�ṹ
	SPI_InitStruction.SPI_Direction=SPI_Direction_2Lines_FullDuplex;      //˫��˫��ȫ˫��
	SPI_InitStruction.SPI_FirstBit=SPI_FirstBit_MSB;                      //���ݴ����MSBλ��ʼ  
	SPI_InitStruction.SPI_Mode=SPI_Mode_Master;                           //����Ϊ��SPI
	SPI_InitStruction.SPI_NSS=SPI_NSS_Soft;                               //�ڲ�NSS�ź���SSIλ���ƣ���ʵNSS����Ƭѡ
	
	SPI_Init(SPI2,&SPI_InitStruction);
	
	SPI_Cmd(SPI2,ENABLE);                            //ʹ��SPI����
	
	SPI2_Write_Read_Byte(0xff);                      //��������
}

/*
 * @brief  Ӳ��SPI2��������պ���
 *
 * @param  TX_Data�����͵�����8λ
 *         
 * @retval SPI���ܵ�����8λ
 *
 */
u8 SPI2_Write_Read_Byte(uint8_t TX_Data)
{
	u8 cyc=0;
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE))
	{
		cyc++;
		if(cyc>=200)return 0;
	}
	SPI_I2S_SendData(SPI2,TX_Data);
	cyc=0;
	
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE))
	{
		cyc++;
		if(cyc>=200)return 0;
	}
	
  return SPI_I2S_ReceiveData(SPI2);
}
