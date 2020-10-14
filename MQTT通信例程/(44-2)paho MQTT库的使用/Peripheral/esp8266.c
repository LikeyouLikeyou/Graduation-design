#include "esp8266.h"
#include "printf.h"
#include "usart3.h"
#include "delay.h"
#include <stdio.h>
#include <string.h>


u8 AT_Command(char* dest,char* src,u16 delay_nms)
{
    delay_nms/=10;                   //超时时间

    while(strstr(dest,src)==0 && delay_nms--)     //等待串口接收完毕或超时退出，因为当strstr找到字符串时便会返回地址使while不成立于是跳出
    {
        delay_ms(10);
    }

    if(delay_nms)                      //上面 retry_nms减到0跳出while时这里会变成0xFFFF
        return 1;

    return 0;
}

static u8 ConAP(char *ssid,char *pwd)
{
    memset(rxbuf,0,256);
    sprintf((char*)txbuf,"AT+CWJAP_CUR=\"%s\",\"%s\"\r\n",SSID,PWD);//连接目标AP
    Usart3_SendString((char*)txbuf);
    if(AT_Command((char*)rxbuf,"OK",8000)!=0)                      //连接成功且分配到IP
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


static u8 ConCloudServer(char *protocol,char *ipaddress,int port)
{
    /* 连接服务器 */
    Usart3_SendString("+++");
    delay_ms(50);
    Usart3_SendString("+++");
    delay_ms(50);
    delay_ms(500);
    memset(rxbuf,0,256);
    sprintf((char*)txbuf,"AT+CIPSTART=\"%s\",\"%s\",%d\r\n",protocol,ipaddress,port);
    Usart3_SendString((char*)txbuf);
    if(AT_Command((char*)rxbuf,"CONNECT",8000) !=0 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void RST_8266(void)
{
    Usart3_SendString("+++");
    delay_ms(50);
    Usart3_SendString("+++");
    delay_ms(50);
    delay_ms(500);
    Usart3_SendString("AT+RST\r\n");
    delay_ms(800);
}

void ESP8266_Init(void)
{
    /* 初始化 */
    memset(rxbuf,0,256);
    memset(txbuf,0,256);
    RST_8266();                                                 	  //01S复位
    memset(rxbuf,0,256);
    Usart3_SendString("AT\r\n");                                  //检测01S是否存在
    while(!AT_Command((char *)rxbuf,"OK",200)) {};                    
    memset(rxbuf,0,256); 
    Usart3_SendString("ATE0\r\n");                                //关闭透传
    while(!AT_Command((char *)rxbuf,"OK",500)) {};                  
    memset(rxbuf,0,256);
    Usart3_SendString("AT+CWMODE_CUR=1\r\n");                    //配置为从机模式
    while(!AT_Command((char *)rxbuf,"OK",200)) {};       
    while(!ConAP(SSID,PWD)) {};                                  //连接热点
    while(!ConCloudServer(TCP,SERVER_IP,SERVER_PORT)) {};        //连接服务器
    memset(rxbuf,0,256);
    Usart3_SendString("AT+CIPMODE=1\r\n");                       //配置为透传模式
    while(!AT_Command((char *)rxbuf,"OK",200)) {};         
    memset(rxbuf,0,256);
    Usart3_SendString("AT+CIPSEND\r\n");                         //开启透传
    while(!AT_Command((char *)rxbuf,">",200));                
}

