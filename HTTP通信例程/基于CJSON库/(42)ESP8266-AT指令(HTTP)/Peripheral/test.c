#include "test.h"


volatile uint8_t ucTcpClosedFlag = 0;

//char cStr [ 1500 ] = { 0 };         //���ͻ���


/*
  *****************************************************************************
  * @Name   : ESP8266_Configuration(void)
  *
  * @Brief  : ��Ҫ��͸��ǰ������·�����ͷ���������
  *
  * @Input  : none
  *
  * @Output : none
  *
  * @Return : none
  *****************************************************************************
 */
void ESP8266_Configuration(void)
{
    printf ( "\r\n�������� ESP8266 ......\r\n" );

    macESP8266_CH_ENABLE();               //����ʱ���ⲿ������д�����̼�ʱ�ⲿ����

    ESP8266_AT_Test ();                   //����AT

    ESP8266_Net_Mode_Choose ( STA );      //ѡ��ΪSTAģʽ

    while ( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );        //��·����

    ESP8266_Enable_MultipleId ( DISABLE );                                               //��Ϊ�ͻ�����������ʧ�ܶ�����

    while ( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );     //���ӷ�����

    while ( ! ESP8266_UnvarnishSend () );             //����͸��

    printf ( "\r\n���� ESP8266 ���\r\n" );
}

/*
  *****************************************************************************
  * @Name   : void Reconnection(void)
  *
  * @Brief  : ����������������Ҫʵ�ֿͻ�����������
  *
  * @Input  : none
  *
  * @Output : none
  *
  * @Return : none
  *****************************************************************************
 */
void Reconnection(void)
{
    uint8_t ucStatus;

    if ( ucTcpClosedFlag )                                             //����Ƿ�ʧȥ����
    {
        ESP8266_ExitUnvarnishSend ();                                    //�˳�͸��ģʽ

        do ucStatus = ESP8266_Get_LinkStatus ();                         //��ȡ����״̬
        while ( ! ucStatus );

        if ( ucStatus == 4 )                                             //ȷ��ʧȥ���Ӻ�����
        {
            printf ( "\r\n���������ȵ�ͷ����� ......\r\n" );

            while ( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );

            while ( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );

            printf ( "\r\n�����ȵ�ͷ������ɹ�\r\n" );

        }

        while ( ! ESP8266_UnvarnishSend () );

    }
}

//void Smartconfig(void)                            //������������û��д��
//{
//	
//			  /*************�˳�͸���ر�TCP���ӷ����´�����*******/

//			  if(key_scan(0)==key_wk_up_press)      //���wk_up�������˳�͸��ģʽ
//				{
//			    ESP8266_ExitUnvarnishSend ();      //�˳�͸��
//					ESP8266_ExitLink();                //�ر�TCP����
//					printf("�˳�͸���ɹ����ر����ӳɹ���\r\n");
//			  }

//				/*************************************************/
//	
//}


/**
  * @brief  ESP8266 ��Sta Tcp Client��͸��
  * @param  ��
  * @retval ��
  */
void ESP8266_StaTcpClient_UnvarnishTest ( void )
{
    char cStr [ 256 ] = { 0 };       //���ͻ���

//		int result; 
		
//		char *p=NULL;
		
    ESP8266_Configuration();         //����Ϊ͸��
		
		
    while ( 1 )
    {

        CreateJsonData();      			//����JSON����

        sprintf ( cStr,POST,strlen(JSON_Data_Buff),JSON_Data_Buff);          //����POST����
//			  sprintf ( cStr,GET,GET_HTTPURL,HOST);  //����GET����

        ESP8266_SendString ( ENABLE, cStr, 0, Single_ID_0 );                 //��������

			
        delay_ms ( 1000 );                                                   //3S�ط�һ��GET����
			
			  printf("����POST�ɹ�!\r\n");
//			  delay_ms ( 1000 );                                                 //3S�ط�һ��GET����
//			  delay_ms ( 1000 );                                                 //3S�ط�һ��GET����

//			  p = (char *)strstr(ESP8266_ReceiveString(ENABLE), "\r\n\r\n") + strlen("\r\n\r\n");
			
//			  result=ParseJsonData(p);
//			  printf("%d\r\n",result);
//        printf("%s\r\n",ESP8266_ReceiveString(ENABLE));                    //�������յ�����ͨ������1��ӡ����,�������Ҫ��ӡ�Ļ�Ҫд����ʱ���棬Ҫ��Ȼ̫�쵼�´�ӡ�������ݣ�ʵ�������յ���

        Reconnection();             //������������
    }
}


