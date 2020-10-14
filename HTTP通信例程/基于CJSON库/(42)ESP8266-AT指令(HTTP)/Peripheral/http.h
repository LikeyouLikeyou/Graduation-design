#ifndef __HTTP_H_
#define __HTTP_H_

#include <stdio.h>
#include <string.h>
#include "stm32f10x.h"
#include "cJSON.h"
#include "usart1.h"

/* GET���� */
/*HTTP GETՈ���ʽ*/
//             GET /%s HTTP/1.1                         \r\n
//             Content-Type: text/html;charset=utf-8    \r\n
//             Accept: */*                              \r\n
//             Host: %s                                 \r\n
//             Connection: Keep-Alive                   \r\n\r\n       //������(��ʽΪ �����ո�URL�ո�汾)
#define GET "GET /%s HTTP/1.1\r\nContent-Type: text/html;charset=utf-8\r\nAccept: */*\r\nHost: %s\r\nConnection: Keep-Alive\r\n\r\n"   //������(��ʽΪ �����ո�URL�ո�汾)

/*HTTP POSTՈ���ʽ*/
//             POST /%s HTTP/1.1                        \r\n
//             Accept: */*                              \r\n
//             Content-Length: %d                       \r\n
//             Content-Type: application/json           \r\n
//             Host: %s                                 \r\n
//             Connection: Keep-Alive                   \r\n\r\n  //������ͷ
//             %s                //����Ϊ����������͵���Ϣ
//#define POST "POST /%s HTTP/1.1\r\nAccept: */*\r\nContent-Length: %d\r\nContent-Type: application/json\r\nHost: %s\r\nConnection: Keep-Alive\r\n\r\n%s"  //������ͷ

#define POST "POST http://47.115.119.0:3001/index  HTTP/1.1\r\nAccept: application/json, text/javascript, */*; q=0.01\r\nContent-Length: %d\r\nHost: 47.115.119.0:3001\r\nContent-Type: application/json\r\nConnection: keep-alive\r\n\r\n%s"

/* ����URL */
#define GET_HTTPURL "index.html"
#define POST_HTTPURL "index.html"

/* �������� */
#define HOST "MyServer"

extern char JSON_Data_Buff[256];


_Bool ParseJsonData(char *pdata);             //����JSON����
void CreateJsonData(void);            //����JSON����

#endif
