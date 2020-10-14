#ifndef  __ESP8266_H
#define	 __ESP8266_H


#include <stdio.h>
#include <stdbool.h>
#include <string.h> 
#include "delay.h"
#include "stm32f10x.h"
#include "rewrite.h"



#if defined ( __CC_ARM   )
#pragma anon_unions
#endif



/******************************* ESP8266 数据类型定义 ***************************/
typedef enum{
	STA,
  AP,
  STA_AP  
} ENUM_Net_ModeTypeDef;


typedef enum{
	 enumTCP,
	 enumUDP,
} ENUM_NetPro_TypeDef;
	

typedef enum{
	Multiple_ID_0 = 0,
	Multiple_ID_1 = 1,
	Multiple_ID_2 = 2,
	Multiple_ID_3 = 3,
	Multiple_ID_4 = 4,
	Single_ID_0 = 5,
} ENUM_ID_NO_TypeDef;
	

typedef enum{
	OPEN = 0,
	WEP = 1,
	WPA_PSK = 2,
	WPA2_PSK = 3,
	WPA_WPA2_PSK = 4,
} ENUM_AP_PsdMode_TypeDef;



/******************************* ESP8266 外部全局变量声明 ***************************/
#define RX_BUF_MAX_LEN     1024                                     //最大接收缓存字节数

extern struct  STRUCT_USARTx_Fram                                  //串口数据帧的处理结构体
{
	char  Data_RX_BUF [ RX_BUF_MAX_LEN ];
	
  union {
    __IO u16 InfAll;
    struct 
		{
		  __IO u16 FramLength       :15;                               // 14:0 
		  __IO u16 FramFinishFlag   :1;                                // 15 
	  } InfBit;
  }; 
	
} strEsp8266_Fram_Record;



/******************************** ESP8266 连接引脚定义 ************************************/
/************************* 这里根据自己的板子上8266引脚作出改变 ****************************/
/********** macESP8266_CH_PD_PIN：下载固件引脚，下载时拉低，运行程序时拉高或悬空 ************/
/********** macESP8266_RST_PIN：复位引脚，拉低即可复位 ************************************/

#define      macESP8266_CH_PD_APBxClock_FUN                   RCC_APB2PeriphClockCmd
#define      macESP8266_CH_PD_CLK                             RCC_APB2Periph_GPIOA 
#define      macESP8266_CH_PD_PORT                            GPIOA
#define      macESP8266_CH_PD_PIN                             GPIO_Pin_15

#define      macESP8266_RST_APBxClock_FUN                     RCC_APB2PeriphClockCmd
#define      macESP8266_RST_CLK                               RCC_APB2Periph_GPIOA
#define      macESP8266_RST_PORT                              GPIOA
#define      macESP8266_RST_PIN                               GPIO_Pin_4

 

#define      macESP8266_USART_BAUD_RATE                       115200

#define      macESP8266_USARTx                                USART3
#define      macESP8266_USART_APBxClock_FUN                   RCC_APB1PeriphClockCmd
#define      macESP8266_USART_CLK                             RCC_APB1Periph_USART3
#define      macESP8266_USART_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define      macESP8266_USART_GPIO_CLK                        RCC_APB2Periph_GPIOB     
#define      macESP8266_USART_TX_PORT                         GPIOB   
#define      macESP8266_USART_TX_PIN                          GPIO_Pin_10
#define      macESP8266_USART_RX_PORT                         GPIOB
#define      macESP8266_USART_RX_PIN                          GPIO_Pin_11
#define      macESP8266_USART_IRQ                             USART3_IRQn
#define      macESP8266_USART_INT_FUN                         USART3_IRQHandler



/*********************************************** ESP8266 函数宏定义 *******************************************/
#define     macESP8266_Usart( fmt, ... )           USART_printf ( macESP8266_USARTx, fmt, ##__VA_ARGS__ ) 
#define     macPC_Usart( fmt, ... )                printf ( fmt, ##__VA_ARGS__ )
//#define     macPC_Usart( fmt, ... )                

#define     macESP8266_CH_ENABLE()                 GPIO_SetBits ( macESP8266_CH_PD_PORT, macESP8266_CH_PD_PIN )
#define     macESP8266_CH_DISABLE()                GPIO_ResetBits ( macESP8266_CH_PD_PORT, macESP8266_CH_PD_PIN )

#define     macESP8266_RST_HIGH_LEVEL()            GPIO_SetBits ( macESP8266_RST_PORT, macESP8266_RST_PIN )
#define     macESP8266_RST_LOW_LEVEL()             GPIO_ResetBits ( macESP8266_RST_PORT, macESP8266_RST_PIN )



/****************************************** ESP8266 函数声明 ***********************************************/
void                     ESP8266_Init                        ( void );                                                                                     //ESP8266初始化
void                     ESP8266_Rst                         ( void );                                                                                     //硬件复位
bool                     ESP8266_Cmd                         ( char * cmd, char * reply1, char * reply2, u32 waittime );                                   //发AT指令
void                     ESP8266_AT_Test                     ( void );                                                                                     //AT指令复位
bool                     ESP8266_Net_Mode_Choose             ( ENUM_Net_ModeTypeDef enumMode );                                                            //STA/AP/STA&AP模式选择
bool                     ESP8266_JoinAP                      ( char * pSSID, char * pPassWord );                                                           //连接路由器
bool                     ESP8266_BuildAP                     ( char * pSSID, char * pPassWord, ENUM_AP_PsdMode_TypeDef enunPsdMode );                      //创建WiFi热点
bool                     ESP8266_Enable_MultipleId           ( FunctionalState enumEnUnvarnishTx );                                                        //WF-ESP8266模块启动多连接，用于
bool                     ESP8266_Link_Server                 ( ENUM_NetPro_TypeDef enumE, char * ip, char * ComNum, ENUM_ID_NO_TypeDef id);                //WF-ESP8266模块连接外部服务器
bool                     ESP8266_StartOrShutServer           ( FunctionalState enumMode, char * pPortNum, char * pTimeOver );                              //WF-ESP8266模块开启或关闭服务器模式
uint8_t                  ESP8266_Get_LinkStatus              ( void );                                                                                     //获得连接状态
uint8_t                  ESP8266_Get_IdLinkStatus            ( void );                                                                                     //获取 WF-ESP8266 的连接状态，较适合单端口时使用
uint8_t                  ESP8266_Inquire_ApIp                ( char * pApIp, uint8_t ucArrayLength );                                                      //获取 F-ESP8266 的 AP IP
bool                     ESP8266_UnvarnishSend               ( void );                                                                                     //配置WF-ESP8266模块进入透传发送
void                     ESP8266_ExitUnvarnishSend           ( void );                                                                                     //退出透传模式
bool                     ESP8266_SendString                  ( FunctionalState enumEnUnvarnishTx, char * pStr, u32 ulStrLength, ENUM_ID_NO_TypeDef ucId ); //发送字符串
char *                   ESP8266_ReceiveString               ( FunctionalState enumEnUnvarnishTx );                                                        //接收字符串


void                     ESP8266_ExitLink                    (void);                                                                                       //关闭 TCP/UDP/SSL 传输,这里仅适用于单连接



#endif


