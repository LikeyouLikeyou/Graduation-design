#include "GPS.h"
#include "printf.h"
#include <string.h>
#include "usart3.h"

void errorLog(int num)
{

    while (1)
    {
        printf("ERROR%d\r\n",num);
    }
}

void parseGpsBuffer()     //解析GPS数据
{
    char *subString;
    char *subStringNext;
    char i = 0;
    if (Save_Data.isGetData)
    {
        Save_Data.isGetData = false;
        printf("**************\r\n");
        printf("%s\r\n",Save_Data.GPS_Buffer);


        for (i = 0 ; i <= 6 ; i++)
        {
            if (i == 0)
            {
                if ((subString = strstr(Save_Data.GPS_Buffer, ",")) == NULL)
                    errorLog(1);	//解析错误
            }
            else
            {
                subString++;
                if ((subStringNext = strstr(subString, ",")) != NULL)
                {
                    char usefullBuffer[2];
                    switch(i)
                    {
                    case 1:
                        memcpy(Save_Data.UTCTime, subString, subStringNext - subString);
                        break;	//获取UTC时间
                    case 2:
                        memcpy(usefullBuffer, subString, subStringNext - subString);
                        break;	//获取UTC时间
                    case 3:
                        memcpy(Save_Data.latitude, subString, subStringNext - subString);
                        break;	//获取纬度信息
                    case 4:
                        memcpy(Save_Data.N_S, subString, subStringNext - subString);
                        break;	//获取N/S
                    case 5:
                        memcpy(Save_Data.longitude, subString, subStringNext - subString);
                        break;	//获取经度信息
                    case 6:
                        memcpy(Save_Data.E_W, subString, subStringNext - subString);
                        break;	//获取E/W

                    default:
                        break;
                    }

                    subString = subStringNext;
                    Save_Data.isParseData = true;
                    if(usefullBuffer[0] == 'A')
                        Save_Data.isUsefull = true;
                    else if(usefullBuffer[0] == 'V')
                        Save_Data.isUsefull = false;

                }
                else
                {
                    errorLog(2);	//解析错误
                }
            }


        }
    }
}

void printGpsBuffer()     //串口输出GPS数据
{
    if (Save_Data.isParseData)
    {
        Save_Data.isParseData = false;

        printf("Save_Data.UTCTime = ");
        printf("%s\r\n",Save_Data.UTCTime);
        printf("\r\n");

        if(Save_Data.isUsefull)
        {
            Save_Data.isUsefull = false;
            printf("Save_Data.latitude = ");
            printf("%s\r\n",Save_Data.latitude);
            printf("\r\n");


            printf("Save_Data.N_S = ");
            printf("%s\r\n",Save_Data.N_S);
            printf("\r\n");

            printf("Save_Data.longitude = ");
            printf("%s\r\n",Save_Data.longitude);
            printf("\r\n");

            printf("Save_Data.E_W = ");
            printf("%s\r\n",Save_Data.E_W);
            printf("\r\n");
        }
        else
        {
            printf("GPS DATA is not usefull!\r\n");
        }

    }
}



