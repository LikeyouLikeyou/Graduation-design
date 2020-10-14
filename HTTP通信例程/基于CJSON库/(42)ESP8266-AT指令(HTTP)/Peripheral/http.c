#include "http.h"
#include "stdlib.h"

char JSON_Data_Buff[256];


/*
  *****************************************************************************
  * @Name   : _Bool ParseJsonData(char *pdata)
  *
  * @Brief  : 解析接收的JSON数据
  *
  * @Input  : none
  *
  * @Output : none
  *
  * @Return : 是否解析JSON数据
  *****************************************************************************
 */
_Bool ParseJsonData(char *pdata)
{
    int i,j,size,size2;
    cJSON *json=NULL;
    cJSON *node=NULL;
    cJSON *tnode=NULL;
    cJSON *tnode2=NULL;
    char *json_data=pdata;

    /* 这里就是完整的输出一个JSON对象结构 */
    json = cJSON_Parse(json_data);                         //从JSON数据缓冲区解析JSON的对象结构
    node = cJSON_GetObjectItemCaseSensitive(json, "command");
    if (node == NULL)
        printf("command: no\n");
    else
        printf("command: ok\n");


    if (node->type == cJSON_Array)                         //看command中值的类型是不是数组类型
    {
        printf("command array size is %d\r\n", cJSON_GetArraySize(node));    //输出数组的大小

        size = cJSON_GetArraySize(node);                             //获取数组的大小
        for (i = 0; i<size; i++)
        {
            tnode = cJSON_GetArrayItem(node, i);                    //在数组查找指定下标的节点对象

            if (tnode->type == cJSON_String)                        //判断其是不是字符串类型，是则以字符串类型输出
                printf("%d: %s\r\n", i, tnode->valuestring);
            else if (tnode->type == cJSON_Object)                   //否则如果为json对象
            {
                size2 = cJSON_GetArraySize(tnode);                  //则获取数组的大小
                for (j = 0; j<size2; j++)
                {
                    tnode2 = cJSON_GetArrayItem(tnode, j);          //然后将数组中的所有值都输出来
                    if (tnode2->type == cJSON_String)
                        printf("%d-%d: %s\r\n", i, j, tnode2->valuestring);
                    else
                        printf("tnod2 type is err\r\n");
                }
            }
            else                                                    //否则如果数组中的既不是字符串，又不是对象，那就按照整形输出
                printf("node type is not string, value = %d\r\n", tnode->type);
        }
        cJSON_Delete(json);           //释放申请的JSON结构缓存空间
        return 0;
    }
    else
    {
        cJSON_Delete(json);           //释放申请的JSON结构缓存空间
        return 1;
    }
}

/*
  *****************************************************************************
  * @Name   : void CreateJsonData(void)
  *
  * @Brief  : 创建JSON数据
  *
  * @Input  : none
  *
  * @Output : none
  *
  * @Return : none
  *****************************************************************************
 */
void CreateJsonData(void)
{
    /* 创建cJSON结构体指针 */
    cJSON *json = NULL;
    cJSON *array = NULL;
    cJSON *obj = NULL;
	  char *temp=NULL;

	  memset(JSON_Data_Buff,0,256);
    /* 创建JSON结构对象 */
    json = cJSON_CreateObject();

    /* 将第一个数组增加到JSON对象中 */
    array = cJSON_CreateArray();                                    //创建一个空数组，我们要创建一个空数组，然后里面放两个对象
    cJSON_AddItemToObject(json, "data", array);                     //向对象中添加一个条目，这里可以看到我们向data对象中添加了一个数组


    obj = cJSON_CreateObject();                                     //创建一个空数组中的第一个对象
    cJSON_AddItemToArray(array, obj);                               //向数组中添加一个条目，这里我们可以看到我们向数组中添加的是下面这三个名称和值
    cJSON_AddItemToObject(obj, "Tem", cJSON_CreateNumber(38));    //向对象中添加条目，这里添加的是   "name":"Faye"
    cJSON_AddItemToObject(obj, "Hum", cJSON_CreateNumber(50));      //向对象中添加字符串  "address":"beijing"
    cJSON_AddItemToObject(obj, "ill", cJSON_CreateNumber(70));      //向对象中添加字符串  "age":"20"

    obj = cJSON_CreateObject();                                     //创建一个空数组中的第二个对象
    cJSON_AddItemToArray(array, obj);                               //向这个对象中添加一个条目
    cJSON_AddItemToObject(obj, "LED", cJSON_CreateNumber(0));       //向对象中添加条目，这里添加的是   "name":"andy"

    temp = cJSON_Print(json);                                      //将创建好的JSON结构对象转换为字符串
    
		strcpy(JSON_Data_Buff, temp);                                  //将对象复制到buff缓冲区当中
		
    free(temp);                                                    //这里要释放temp，要不然过不了多久cJSON_Print函数就会导致内存溢出
    cJSON_Delete(json);                                            //释放申请的JSON结构缓存空间
}


/* 上面只传命令下来，GET获得的数据 */
/*{
"command":
    [
      {
         "LED":"0"
      },
      {
         "WIND":"0"
      }
    ]
}*/

/* 下面只传数据上去，POST所传的数据 */
/*{
   "data":[
             {
                "Tem":37.5,
                "Hum":20,
                "ill":70
             },
             {
                "LED":0
             }
          ]
}*/



