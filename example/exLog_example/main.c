
#include "../../exLib/exLib.h"

const char *tag="test";


void functionA()
{

EX_LOGV(tag,"hello world\r\n");
EX_LOGD(tag,"hello world\r\n");
EX_LOGI(tag,"hello world\r\n");
EX_LOGW(tag,"hello world\r\n");
EX_LOGE(tag,"hello world\r\n");
EX_LOGU(tag,"hello world\r\n");
}
void main()
{
    while(1)
    {
        
        functionA();
        
    }

    
}