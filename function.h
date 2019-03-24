//
//  function.c
//  Phonebook
//
//  Created by sanho lee on 2019/03/12.
//  Copyright © 2019 sanho lee. All rights reserved.
//
#ifndef __function_header__
#define __function_header__
#include "Struct.h"


int getMenu(void);   // menu를 출력하고, 목차 번호를 입력받아 반환함.
void clrInBff(void);     //입력버퍼를 없애주는 함수


//switch문에 의해 동작되는 각 기능의 함수를 정의
int insert(void);
int prtA(void);
void search(void);
void del(void);

void exit_prog(void);



#endif
