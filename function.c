//
//  function.c
//  Phonebook
//
//  Created by sanho lee on 2019/03/19.
//  Copyright © 2019 sanho lee. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "Struct.h"
#include "function.h"

int getMenu(void)   // menu를 출력하고, 목차 번호를 입력받아 반환함.
{
    int select;
    int i;
    char *arr[7]=
    {"***** MENU *****",
        "Insert",
        "Delete",
        "Search",
        "Print All",
        "Exit",
        "Choose the item : "};
    
    puts(arr[0]);
    for(i=0;i<5;i++)
        printf("%d.%s\n",i+1,arr[i+1]);
    
    fputs(arr[6], stdout);  // choose the item 출력!
    scanf("%d", &select);
    getchar();              // 엔터키 삭제!
    
    return select;
}

void clrInBff(void)     //입력버퍼를 없애주는 함수
{
    while (getchar()!='\n');
}



void insert(void)
{
    HumInfo *temp1=(HumInfo *)malloc(sizeof(temp1));
    
    FILE *fp=fopen(Filename, "a+");
    if (fp==NULL)
    {
        printf("파일오픈 실패! \n");
    }
    
    printf("\n[ Insert ]\n");
    printf("Input Name : "); scanf("%s", temp1->name);         //scanf를 이용해서 temp구조체로 데이터 입력함.
    printf("Input Tel Number : "); scanf("%s", temp1->phoneNum);
    
    
    //fgets로 읽으면, 마지막 문자에 \n이 입력되어있으므로 이 부분을 0으로 만들어줘야 한다.
    //구조체 안에 char형 배열에 접근해서 0으로 만들어주는게 훨씬 더 번거로워서 scanf로 처리함.
    
    fputs(temp1->name, fp);                  // 입력받은 데이터를 파일에 출력
    fputs("\t", fp);
    fputs(temp1->phoneNum, fp);
    fputs("\n", fp);
    
    
    printf("\n");                           //화면출력
    puts("\t\t[ Data Inserted! ]\n");
    
    fclose(fp);
    
}
/*
void delete()
{
    
}

void search()
{
    
}
*/
void prtA(void)
{
    
    HumInfo *temp_p=(HumInfo *)malloc(sizeof(temp_p));
    int cnt=0;
    int i=0;
    
    FILE *fp_pA=fopen(Filename, "rt");
    if (fp_pA==NULL)
    {
        printf("파일 오픈 실패 ! \n");
    }
    
    while (!feof(fp_pA))
    {
        fscanf(fp_pA, "%s\t%s",(temp_p+i)->name,(temp_p+i)->phoneNum);
        i++;
    }
    
    cnt=i-1;
    
    fputs("\n[ List of Phonenumber ]\n\n", stdout);
    
    for(i=0;i<cnt;i++){
        printf("%d. name : %s",i+1,temp_p[i].name);
        fputs("  \t", stdout);
        printf("Tel : %s\n",temp_p[i].phoneNum);
    }
    
    fclose(fp_pA);
    
}

void exit_prog(void)
{
    printf("[ 프로그램 종료! ]\n");
}
