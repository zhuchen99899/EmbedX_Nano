
#include "../../exLib/exLib.h"

const char *tag="test";


void functionA()
{
EX_LOG_COLOR_CLEAR();
EX_LOG_COLOR_SET(LOG_RED,LOG_DARK);
EX_LOGD(tag,"hello world\r\n");
EX_LOG_COLOR_CLEAR();
EX_LOG_COLOR_SET(LOG_GREEN,LOG_YELLOW);
EX_LOGD(tag,"USE COLOFUL LOG!\r\n");
EX_LOG_COLOR_CLEAR();

}
void main()
{
    while(1)
    {
        
        functionA();
        
    }

    
}