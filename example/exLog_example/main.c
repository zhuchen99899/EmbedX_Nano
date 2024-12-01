
#include "../../exLib/ex_lib.h"

EX_TAG("MAIN");


void functionA()
{
EX_LOGV("hello world\r\n");
EX_LOGD("hello world\r\n");
EX_LOGI("hello world\r\n");
EX_LOGW("hello world\r\n");
EX_LOGE("hello world\r\n");
EX_LOGU("hello world\r\n");
}

void main()
{
    
    while(1)
    {
        
        functionA();
        
    }

    
}