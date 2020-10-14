#include "esp8266.h"
#include "printf.h"
#include "usart3.h"
#include "delay.h"
#include <stdio.h>
#include <string.h>


u8 AT_Command(char* dest,char* src,u16 delay_nms)
{
    delay_nms/=10;                   //��ʱʱ��

    while(strstr(dest,src)==0 && delay_nms--)     //�ȴ����ڽ�����ϻ�ʱ�˳�����Ϊ��strstr�ҵ��ַ���ʱ��᷵�ص�ַʹwhile��������������
    {
        delay_ms(10);
    }

    if(delay_nms)                      //���� retry_nms����0����whileʱ�������0xFFFF
        return 1;

    return 0;
}

static u8 ConAP(char *ssid,char *pwd)
{
    memset(rxbuf,0,256);
    sprintf((char*)txbuf,"AT+CWJAP_CUR=\"%s\",\"%s\"\r\n",SSID,PWD);//����Ŀ��AP
    Usart3_SendString((char*)txbuf);
    if(AT_Command((char*)rxbuf,"OK",8000)!=0)                      //���ӳɹ��ҷ��䵽IP
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
    /* ���ӷ����� */
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
    /* ��ʼ�� */
    memset(rxbuf,0,256);
    memset(txbuf,0,256);
    RST_8266();                                                 	  //01S��λ
    memset(rxbuf,0,256);
    Usart3_SendString("AT\r\n");                                  //���01S�Ƿ����
    while(!AT_Command((char *)rxbuf,"OK",200)) {};                    
    memset(rxbuf,0,256); 
    Usart3_SendString("ATE0\r\n");                                //�ر�͸��
    while(!AT_Command((char *)rxbuf,"OK",500)) {};                  
    memset(rxbuf,0,256);
    Usart3_SendString("AT+CWMODE_CUR=1\r\n");                    //����Ϊ�ӻ�ģʽ
    while(!AT_Command((char *)rxbuf,"OK",200)) {};       
    while(!ConAP(SSID,PWD)) {};                                  //�����ȵ�
    while(!ConCloudServer(TCP,SERVER_IP,SERVER_PORT)) {};        //���ӷ�����
    memset(rxbuf,0,256);
    Usart3_SendString("AT+CIPMODE=1\r\n");                       //����Ϊ͸��ģʽ
    while(!AT_Command((char *)rxbuf,"OK",200)) {};         
    memset(rxbuf,0,256);
    Usart3_SendString("AT+CIPSEND\r\n");                         //����͸��
    while(!AT_Command((char *)rxbuf,">",200));                
}

