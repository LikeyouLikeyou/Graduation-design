//================================================================================
//STM32F103         �๦��ͨѶ������ʾģ��
//================================================================================
//SPI_S.C/H         SPI���������⺯��                          BY SAGAHDS 20170804
//================================================================================
#ifndef __SPI_S_H 
#define __SPI_S_H
//================================================================================
extern unsigned char SPI_FLAG;           			 //SPI�ı�־λ
						 #define SPI1_FLAG_ENABLE    0x01  //��1����SPI1
						 #define SPI2_FLAG_ENABLE    0x02  //��1����SPI2
//================================================================================
//SPI1��Ƭѡ����	//Ӳ��SPI��CSN�ܽ�,оƬ����������λ,��Ҫ�Լ�д������λ
#define SPI1_CSN_LOW()    GPIO_ResetBits(GPIOC, GPIO_Pin_4)
#define SPI1_CSN_HIGH()   GPIO_SetBits(GPIOC, GPIO_Pin_4)
//SPI2��Ƭѡ����	//SPI2���ֵĳ���Ŀǰûд,���Ҳ���
#define SPI2_CSN_LOW()    GPIO_ResetBits(GPIOB, GPIO_Pin_12)
#define SPI2_CSN_HIGH()   GPIO_SetBits(GPIOB, GPIO_Pin_12)
//================================================================================
//SPI1��غ��� BY SAGAHDS 20180413
void SPI1_Configuration(unsigned char Enable);      //SPI1��ʼ��
unsigned char SPI1_ReadWriteByte(unsigned char data);	//SPI1��дһ���ֽ�
unsigned char SPI1_RW_S(unsigned char byte);		//Read or Write a byte by SPI BUS		//��ʵ����һ��һ����SPI1_ReadWriteByte();
unsigned char SPI1_RW_Reg_S(unsigned char reg, unsigned char byte);	//Write a byte to register by SPI BUS,�������üĴ�������
unsigned char SPI1_Read_S(unsigned char reg);	//Read a byte from a register by SPI BUS,���ڶ�ȡ�Ĵ�������
         void SPI1_Write_S(unsigned char byte);					//Write a byte to SPI BUS
unsigned char SPI1_Read_Buf_S(unsigned char reg, unsigned char *pBuf, unsigned char bytes); 	//Read a buff as bytes from register by SPI BUS,��������ʱ��ȡFIFO������
unsigned char SPI1_Write_Buf_S(unsigned char reg, unsigned char *pBuf, unsigned char bytes);	//Write a buff as bytes to register by SPI BUS,��������ʱд�����鵽FIFO
//SPI2��غ��� BY SAGAHDS 20180413
void SPI2_Configuration(unsigned char Enable);      //SPI2��ʼ��
unsigned char SPI2_ReadWriteByte(unsigned char data);	//SPI2��дһ���ֽ�
unsigned char SPI2_RW_S(unsigned char byte);		//Read or Write a byte by SPI BUS		//��ʵ����һ��һ����SPI2_ReadWriteByte();
unsigned char SPI2_RW_Reg_S(unsigned char reg, unsigned char byte);	//Write a byte to register by SPI BUS,�������üĴ�������
unsigned char SPI2_Read_S(unsigned char reg);	//Read a byte from a register by SPI BUS,���ڶ�ȡ�Ĵ�������
         void SPI2_Write_S(unsigned char byte);					//Write a byte to SPI BUS
unsigned char SPI2_Read_Buf_S(unsigned char reg, unsigned char *pBuf, unsigned char bytes); 	//Read a buff as bytes from register by SPI BUS,��������ʱ��ȡFIFO������
unsigned char SPI2_Write_Buf_S(unsigned char reg, unsigned char *pBuf, unsigned char bytes);	//Write a buff as bytes to register by SPI BUS,��������ʱд�����鵽FIFO
//SPI2��غ���,ENC����ר�� BY SAGAHDS 20180413
unsigned char	SPI2_ReadWrite(unsigned char writedat);	//BY SAGAHDS 20180322
//================================================================================
#endif
//================================================================================


