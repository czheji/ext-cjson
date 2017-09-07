//
// Created by dengyu on 2017/5/11.
//

#include"cJSON.h"
#include<stdio.h>
#include <stdlib.h>

int main()
{
    FILE *file;
    long len;char *data;
    int i,j,k;

    file = fopen("D:\\gitZcsmart\\core-ckeys\\ext\\cjson\\tests\\Domain.json","rb");
    fseek(file,0,SEEK_END);
    len=ftell(file);
    fseek(file,0,SEEK_SET);
    data=(char*)malloc(len+1);
    fread(data,1,len,file);
    fclose(file);

    cJSON *json;
    json=cJSON_Parse(data);
    if (!json) {
        printf("Error before: [%s]\n",cJSON_GetErrorPtr());
        return 0;
    }

    //char *out;
    //out=cJSON_Print(json);
    //printf("%s\n",out);
    //free(out);

    //解析
    cJSON *domain = cJSON_GetObjectItem(json,"Domain");
    cJSON *type = cJSON_GetObjectItem(domain,"type");
    cJSON *name = cJSON_GetObjectItem(domain,"name");
    cJSON *id_hash = cJSON_GetObjectItem(domain,"id-hash");
    cJSON *sign_hash = cJSON_GetObjectItem(domain,"sign-hash");
    char *strSH = cJSON_Print(sign_hash);
    printf("sign_hash:%s\n",strSH);

    //ska
    int ska_size;
    cJSON *ska = cJSON_GetObjectItem(domain,"ska");
    cJSON *itemSka;
    char *strSka = NULL;
    if(ska)
    {
        ska_size = cJSON_GetArraySize(ska);
        for(i=0;i<ska_size;i++)
        {
            itemSka = cJSON_GetArrayItem(ska,i);
            strSka = cJSON_Print(itemSka);
            printf("%s\n",strSka);
        }
    }

    //sub domain
    cJSON *subdm_ids_array = cJSON_GetObjectItem(domain,"subdm-ids");
    int subdm_size = cJSON_GetArraySize(subdm_ids_array);
    int subdm_ids_size;
    cJSON *subdm_ids_item;
    cJSON *subdm_ids;
    cJSON *subdm_id;
    char *strId = NULL;
    for(j=0;j<subdm_size;j++)
    {
        subdm_ids_item = cJSON_GetArrayItem(subdm_ids_array,j);
        if(subdm_ids_item)
        {
            subdm_ids = cJSON_GetObjectItem(subdm_ids_item,"subdm-id");
            subdm_ids_size = cJSON_GetArraySize(subdm_ids);
            for (k=0;k<subdm_ids_size;k++)
            {
                subdm_id = cJSON_GetArrayItem(subdm_ids,k);
                strId = cJSON_Print(subdm_id);
                printf("subdm_id:%s\n",strId);
            }
        }
    }

    //g
    cJSON *g = cJSON_GetObjectItem(domain,"g");
    cJSON *x = cJSON_GetObjectItem(g,"x");
    char *strX = cJSON_Print(x);
    printf("gx:%s\n",strX);
    cJSON *y = cJSON_GetObjectItem(g,"y");
    char *strY = cJSON_Print(y);
    printf("gy:%s\n",strY);
    cJSON *z = cJSON_GetObjectItem(g,"z");
    char *strZ = cJSON_Print(z);
    printf("gz:%s\n",strZ);

    cJSON_Delete(json);
    return 1;
}