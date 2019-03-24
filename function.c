//
//  function.c
//  Phonebook
//
//  Created by sanho lee on 2019/03/19.
//  Copyright © 2019 sanho lee. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    
    
    puts(""); // 처음실행시 한줄 개행
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



int insert(void)
{
    HumInfo *temp1=(HumInfo *)malloc(sizeof(temp1));
    
    FILE *fp=fopen(Filename, "a+");
    if (fp==NULL)
    {
        printf("파일오픈 실패! \n");
        return -1;
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
    
    free(temp1);
    fclose(fp);
    return 0;
}

void del(void)
{
    FILE *fp_d=fopen(Filename, "rt");
    if (fp_d==NULL)
    {
        printf("파일 오픈 실패 ! \n");
    }
    
    
    HumInfo *temp_d=(HumInfo *)malloc(sizeof(temp_d));
    int i=0;
    int j=0;
    int cnt=0;
    unsigned long nameLen=0;
    char word[10];      // 검색할 이름 정보

    
    while (!feof(fp_d))        //파일에 기록된 정보 스캔
    {
        fscanf(fp_d, "%s\t%s",(temp_d+i)->name,(temp_d+i)->phoneNum);
        i++;
    }
    
    cnt=i-1;
    
    // 여기까지는 prtA과 동일함, 즉, 파일내용을 스캔함.
    
    //  검색할 이름을 입력받음
    printf("[ Delete ]\n");
    printf("NAME : ");  scanf("%s", word);
    clrInBff();
    
    i=0;    //이름 위치 인덱스
    j=0;    //이름 글자 인덱스
    
    while (strlen(word)!=j)
    {
        nameLen=strlen((temp_d+i)->name);   //  name의 문자열 길이를 비교함, 다를 경우 다음 단어 검색
        if (strlen(word)!=nameLen)
            i++;
        else if(word[j]!=(temp_d+i)->name[j])   //  길이가 같을경우, 단어의 첫번째 문자부터 검사
            i++;
        else
            j++;
    }
    
    
    
    
    printf("\n[ 입력한 정보 ] \n");
    printf("NAME : %s\tTel : %s\n",(temp_d+i)->name,(temp_d+i)->phoneNum);  // 검색한 사람의 이름 전화번호 출력!
    
    fclose(fp_d);
    
    FILE *fp_dw=fopen(Filename, "wt");
    if (fp_dw==NULL)
    {
        printf("파일 오픈 실패 ! \n");
    }
    
    
    //삭제 기능은 여기부터!
    
    cnt--;
    while(i!=cnt)       // 삭제는 덮어씌우기로 구현
    {
        strcpy((temp_d+i)->name, (temp_d+i+1)->name);
        strcpy((temp_d+i)->phoneNum, (temp_d+i+1)->phoneNum);
        i++;
    }
    printf("\n [ Data deleted ! ]\n");
    
    
    //삭제 후 구조체 정보를 파일로 다시 재 입력
    
    for(i=0;i<cnt;i++)
    {
        fputs((temp_d+i)->name, fp_dw);                  // 데이터 파일에 출력
        fputs("\t", fp_dw);
        fputs((temp_d+i)->phoneNum, fp_dw);
        fputs("\n", fp_dw);
    }
    
    free(temp_d);
    fclose(fp_dw);
}


void search()        //검색 기능
{
    
    HumInfo *temp_s=(HumInfo *)malloc(sizeof(temp_s));
    int i=0;
    int j=0;
    unsigned long nameLen=0;
    
    
    char word[10];      // 검색할 이름 정보
    
    
    
    FILE *fp_s=fopen(Filename, "rt");
    if (fp_s==NULL)
    {
        printf("파일 오픈 실패 ! \n");
    }
    while (!feof(fp_s))        //파일에 기록된 정보 스캔
    {
        fscanf(fp_s, "%s\t%s",(temp_s+i)->name,(temp_s+i)->phoneNum);
        i++;
    }
    
    // 여기까지는 prtA과 동일함, 즉, 파일내용을 스캔함.
    
    //  검색할 이름을 입력받음
    printf("[ Search ]\n");
    printf("NAME : ");  scanf("%s", word);
    clrInBff();
    
    i=0;    //이름 위치 인덱스
    j=0;    //이름 글자 인덱스
    
    while (strlen(word)!=j)
    {
        nameLen=strlen((temp_s+i)->name);   //  name의 문자열 길이를 비교함, 다를 경우 다음 단어 검색
        if (strlen(word)!=nameLen)
            i++;
        else if(word[j]!=(temp_s+i)->name[j])   //  길이가 같을경우, 단어의 첫번째 문자부터 검사
            i++;
        else
            j++;
    }
    
    printf("\n[ 입력한 정보 검색 결과 ] \n");
    printf("NAME : %s\tTel : %s\n",(temp_s+i)->name,(temp_s+i)->phoneNum);  // 검색한 사람의 이름 전화번호 출력!
    

    free(temp_s);
    fclose(fp_s);
}


int prtA(void)
{
    
    HumInfo *temp_p=(HumInfo *)malloc(sizeof(temp_p));
    int cnt=0;
    int i=0;
    
    FILE *fp_pA=fopen(Filename, "rt");
    if (fp_pA==NULL)
    {
        printf("파일 오픈 실패 ! \n");
        return -1;
    }
    
    while (!feof(fp_pA))        //파일에 기록된 정보 스캔
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
    printf("\n");
    
    free(temp_p);
    fclose(fp_pA);
    return 0;
}

void exit_prog(void)
{
    printf("[ 프로그램 종료! ]\n");
}
