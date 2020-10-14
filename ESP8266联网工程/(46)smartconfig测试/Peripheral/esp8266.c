#include "esp8266.h"


static uint8_t AT_Set(char* buff,char* src,u16 retry_nms)
{
    memset(rxbuf,0,256);
    Usart3_SendString(buff);         //����ATָ��

    retry_nms/=10;                   //��ʱʱ��
    while(strstr((char*)rxbuf,src)==0 && retry_nms--)     //�ȴ����ڽ�����ϻ�ʱ�˳�����Ϊ��strstr�ҵ��ַ���ʱ��᷵�ص�ַʹwhile��������������
    {
        delay_ms(10);
    }

    if(retry_nms)                      //���� retry_nms����0����whileʱ�������0xFFFF
        return 1;

    return 0;
}

void Smartconfig(void)                   //smartconfig����
{
    uint8_t sta=0;

    /* �˳�͸�� */
    Usart3_SendString("+++");
    delay_ms(50);
    Usart3_SendString("+++");
    delay_ms(50);
    delay_ms(500);

    /* ��λ */
    Usart3_SendString("AT+RST\r\n");
    delay_ms(800);

    if(sta==0)              //�ָ���������
    {
        if(AT_Set("AT+RESTORE\r\n","ready",800)==1)
        {
            sta++;
        }
        else
        {
            sta=0;
        }
    }

    if(sta==1)              //�رջ���
    {
        if(AT_Set("ATE0\r\n","OK",500)==1)
        {
            sta++;
        }
        else
        {
            sta=0;
        }
    }

    if(sta==2)              //���õ�ǰ Wi-Fi ģʽ�����浽 Flash����������Ϊstationģʽ
    {
        if(AT_Set("AT+CWMODE_DEF=1\r\n","OK",200)==1)
        {
            sta++;
        }
        else
        {
            sta=0;
        }
    }

    if(sta==3)              //�ϵ��Ƿ�?�Զ����ӣ���������Ϊ�ϵ��Զ�����·����
    {
        if(AT_Set("AT+CWAUTOCONN=1\r\n","OK",200)==1)
        {
            sta++;
        }
        else
        {
            sta=0;
        }
    }

    if(sta==4)              //����smartconfig����������ΪESP-TOUCH
    {
        if(AT_Set("AT+CWSTARTSMART=1\r\n","OK",500)==1)
        {
            sta++;
        }
        else
        {
            sta=0;
        }
    }

    /* �ȴ������ɹ� */
    memset(rxbuf,0,256);
    while(strstr((char*)rxbuf,"smartconfig connected wifi")==0) {}  //�ȴ�15S
    GPIO_ResetBits(GPIOE,GPIO_Pin_5);                               //���óɹ������LED

    if(sta==5)              //�ر�����
    {
        AT_Set("AT+CWSTOPSMART\r\n","OK",200);
    }
}

void ConnectServer(void)                        //���ӷ�����
{
    uint8_t sta=0;
    memset(rxbuf,0,256);

    /* ��λ */
	  Usart3_SendString("AT+RST\r\n");
    delay_ms(800);
	  Usart3_SendString("+++");
    delay_ms(50);
    Usart3_SendString("+++");
    delay_ms(50);
 //   delay_ms(500);


    if(sta==0)
    {
        if(AT_Set("ATE0\r\n","OK",500)!=0)	//�رջ���
        {
            sta++;
        }
        else
        {
            sta=0;
        }
    }

    if(sta==1)
    {
        /* ���ӷ����� */
				delay_ms(500);
        memset(txbuf,0,256);
        sprintf((char*)txbuf,"AT+CIPSTART=\"%s\",\"%s\",%d\r\n",TCP,SERVER_IP,SERVER_PORT);
        Usart3_SendString((char*)txbuf);
        if(AT_Set((char*)txbuf,"CONNECT",8000) !=0 )
        {
            sta++;
        }
        else
        {
            sta=0;
        }
    }

    if(sta==2)
    {
        /* ����Ϊ͸�� */
        if(AT_Set("AT+CIPMODE=1\r\n","OK",200)!=0)
        {
            sta++;
        }
        else
        {
            sta=0;
        }
    }

    if(sta==3)
    {
        /* ����͸�� */
        if(AT_Set("AT+CIPSEND\r\n",">",200)!=0)
        {
            printf("Start Send!\r\n");
        }
        else
        {
            printf("Start Send ERROR!\r\n");
        }
    }
}
