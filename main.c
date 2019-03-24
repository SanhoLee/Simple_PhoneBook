//
//  main.c
//  Phonebook
//
//  Created by sanho lee on 2019/03/20.
//  Copyright © 2019 sanho lee. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>



#include "Struct.h"
#include "function.h"


int main(void)
{
    //FILE *fp_fist=fopen(Filename, "at");
    int getNum=0;
    
    HumInfo *temp_in=(HumInfo *)malloc(sizeof(temp_in));
  
    while(1)
    {
        getNum=getMenu();
        
        switch (getNum)
        {
            case 1:             // 삽입 기능!
                insert();
                break;
                
            case 2:             // 삭제 기능!
                del();
                break;
                
            case 3:             // 검색 기능!
                search();
                break;
                
            case 4:             // 전체 출력기능!
                prtA();
                break;
                
            case 5:             // 프로그램 종료 기능!
            {
                exit_prog();
                break;
                return 0;
            }
            default:
            {
                printf("선택한 번호는 선택지에 없습니다. \n");
                break;
            }
        }
        if (getNum==5)
        {
            break;
            return 0;
        }
    }
}
