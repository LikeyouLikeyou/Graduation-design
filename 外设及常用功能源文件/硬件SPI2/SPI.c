#include "spi.h"

/*
 * @brief  硬件SPI2初始化函数
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
	
	GPIO_InitStruction.GPIO_Mode=GPIO_Mode_AF_PP;                        //复用推挽输出
	GPIO_InitStruction.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStruction.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruction);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);             //默认为高电平
	
	SPI_InitStruction.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_256;    //波特率预分频值为 256       APB1默认输出为72M  这里还要在此基础上256分频
	SPI_InitStruction.SPI_CPHA=SPI_CPHA_1Edge;                            //数据在时钟的第一个边沿采集  
	SPI_InitStruction.SPI_CPOL=SPI_CPOL_Low;                              //时钟悬空时为低
	SPI_InitStruction.SPI_CRCPolynomial=7;                                //CRC值计算的多项式
	SPI_InitStruction.SPI_DataSize=SPI_DataSize_8b;                       //SPI发送接收8位帧结构
	SPI_InitStruction.SPI_Direction=SPI_Direction_2Lines_FullDuplex;      //双线双向全双工
	SPI_InitStruction.SPI_FirstBit=SPI_FirstBit_MSB;                      //数据传输从MSB位开始  
	SPI_InitStruction.SPI_Mode=SPI_Mode_Master;                           //设置为主SPI
	SPI_InitStruction.SPI_NSS=SPI_NSS_Soft;                               //内部NSS信号由SSI位控制，其实NSS就是片选
	
	SPI_Init(SPI2,&SPI_InitStruction);
	
	SPI_Cmd(SPI2,ENABLE);                            //使能SPI外设
	
	SPI2_Write_Read_Byte(0xff);                      //启动传输
}

/*
 * @brief  硬件SPI2发送与接收函数
 *
 * @param  TX_Data：发送的数据8位
 *         
 * @retval SPI接受的数据8位
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
