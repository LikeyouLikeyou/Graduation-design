#include "stm32f10x.h"
#include "spi_S.h"
#include "printf.h"
//================================================================================
unsigned char SPI_FLAG;           			//SPI的标志位

#define SPI2_FLAG_ENABLE    0x02  //置1开启SPI2

//用于RFID-RC522读卡器模块
//BY SAGAHDS 20190321	
void SPI2_Configuration(unsigned char Enable)    
{
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  if(!Enable)
  {
		SPI_FLAG &= ~SPI2_FLAG_ENABLE;
    printf("SPI2 No Installation.\r\n");
    return;
	}

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE); 					//SPI2在APB1


	
	//PB13_CLK PB14_MISO PB15_MOSI
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed =GPIO_Speed_10MHz; 	//	此处可能需要降低速度?
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);  //PB13/14/15上拉

  //PB12_CSN 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);									//拉高CSN失能片选
	
  //SPI2 Config
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; 
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; 
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  //SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
  //SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;//BY SAGAHDS 20180413
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;//定义波特率预分频的值:波特率预分频值为256//RC522所用
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI2, &SPI_InitStructure);
  SPI_Cmd(SPI2, ENABLE); 	//Enable SPI2

	SPI_FLAG |= SPI2_FLAG_ENABLE;
  printf("SPI2 Installation.\r\n");	
}

//==============================================================================
