
#include "../../exLib/ex_lib.h"

#if (EX_TICK_ENABLE==1)
#include "windows.h"

VOID CALLBACK TimerCallback(PVOID lpParameter, BOOLEAN TimerOrWaitFired) {
    // printf("Timer callback fired! tick = %d \n",taskManager_sys_tick());
    ex_systick_inc(1000);//1s刷新一次
}
#endif

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

    
#if (EX_TICK_ENABLE==1)


    HANDLE timer;
    DWORD dueTime= 1000;  // 定时器触发的初始延迟时间（在1000毫秒后）
    DWORD period= 1000; // 定时器触发的周期（每1000毫秒）
        uint32_t flag;
       // 创建一个定时器
    if (!CreateTimerQueueTimer(&timer, NULL, TimerCallback, NULL, dueTime, period,flag)) {
        printf("Failed to create timer\n");
       
    }

#endif
    while(1)
    {
        
        functionA();
        
    }

    
}