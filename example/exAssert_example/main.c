#include "../../exLib/ex_lib.h"

EX_TAG("MAIN");

void functionA(uint32_t arg)
{
    //检查参数
    ex_assert(arg!=0);
}



void functionB(uint32_t ret)
{
//检查返回值/检查id等
ex_assert_id(ret==1,ret);

}

void functionC(uint32_t *arg)
{
//检查指针非空    
ex_assert_not_null(arg);

}


void main()
{
functionA(0);
// functionB(0);
// int *A = NULL;
// functionC(A);
    while (1)
    {
        EX_LOGV("RUNNING\r\n");
    }
    

}