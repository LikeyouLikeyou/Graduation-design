//================================================================================
//STM32F103         多功能通讯控制演示模块
//================================================================================
//SPI_S.C/H         SPI总线驱动库函数                          BY SAGAHDS 20170804
//================================================================================
#ifndef __SPI_S_H 
#define __SPI_S_H
//================================================================================
extern unsigned char SPI_FLAG;           			 //SPI的标志位
						 #define SPI1_FLAG_ENABLE    0x01  //置1开启SPI1
						 #define SPI2_FLAG_ENABLE    0x02  //置1开启SPI2
//================================================================================
//SPI1的片选引脚	//硬件SPI的CSN管脚,芯片本身不负责置位,需要自己写程序置位
#define SPI1_CSN_LOW()    GPIO_ResetBits(GPIOC, GPIO_Pin_4)
#define SPI1_CSN_HIGH()   GPIO_SetBits(GPIOC, GPIO_Pin_4)
//SPI2的片选引脚	//SPI2部分的程序目前没写,暂且不用
#define SPI2_CSN_LOW()    GPIO_ResetBits(GPIOB, GPIO_Pin_12)
#define SPI2_CSN_HIGH()   GPIO_SetBits(GPIOB, GPIO_Pin_12)
//================================================================================
//SPI1相关函数 BY SAGAHDS 20180413
void SPI1_Configuration(unsigned char Enable);      //SPI1初始化
unsigned char SPI1_ReadWriteByte(unsigned char data);	//SPI1读写一个字节
unsigned char SPI1_RW_S(unsigned char byte);		//Read or Write a byte by SPI BUS		//其实就是一对一调用SPI1_ReadWriteByte();
unsigned char SPI1_RW_Reg_S(unsigned char reg, unsigned char byte);	//Write a byte to register by SPI BUS,用于设置寄存器参数
unsigned char SPI1_Read_S(unsigned char reg);	//Read a byte from a register by SPI BUS,用于读取寄存器参数
         void SPI1_Write_S(unsigned char byte);					//Write a byte to SPI BUS
unsigned char SPI1_Read_Buf_S(unsigned char reg, unsigned char *pBuf, unsigned char bytes); 	//Read a buff as bytes from register by SPI BUS,接收数据时读取FIFO的数组
unsigned char SPI1_Write_Buf_S(unsigned char reg, unsigned char *pBuf, unsigned char bytes);	//Write a buff as bytes to register by SPI BUS,发射数据时写入数组到FIFO
//SPI2相关函数 BY SAGAHDS 20180413
void SPI2_Configuration(unsigned char Enable);      //SPI2初始化
unsigned char SPI2_ReadWriteByte(unsigned char data);	//SPI2读写一个字节
unsigned char SPI2_RW_S(unsigned char byte);		//Read or Write a byte by SPI BUS		//其实就是一对一调用SPI2_ReadWriteByte();
unsigned char SPI2_RW_Reg_S(unsigned char reg, unsigned char byte);	//Write a byte to register by SPI BUS,用于设置寄存器参数
unsigned char SPI2_Read_S(unsigned char reg);	//Read a byte from a register by SPI BUS,用于读取寄存器参数
         void SPI2_Write_S(unsigned char byte);					//Write a byte to SPI BUS
unsigned char SPI2_Read_Buf_S(unsigned char reg, unsigned char *pBuf, unsigned char bytes); 	//Read a buff as bytes from register by SPI BUS,接收数据时读取FIFO的数组
unsigned char SPI2_Write_Buf_S(unsigned char reg, unsigned char *pBuf, unsigned char bytes);	//Write a buff as bytes to register by SPI BUS,发射数据时写入数组到FIFO
//SPI2相关函数,ENC部分专用 BY SAGAHDS 20180413
unsigned char	SPI2_ReadWrite(unsigned char writedat);	//BY SAGAHDS 20180322
//================================================================================
#endif
//================================================================================


