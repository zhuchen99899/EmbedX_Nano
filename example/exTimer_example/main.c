
#include "../../component/exThread/ex_thread.h"
#include "../../exLib/ex_lib.h"
#include "../../component/exExport/ex_export.h"
#if (EX_TICK_ENABLE==1)
#include "windows.h"

VOID CALLBACK TimerCallback(PVOID lpParameter, BOOLEAN TimerOrWaitFired) {
    // printf("Timer callback fired! tick = %d \n",taskManager_sys_tick());
    ex_systick_inc();//1ms刷新一次
}
#endif

EX_TAG("MAIN");


static ex_task_scheduler_t default_scheduler=NULL   ;

ex_err_t ex_task_manager_default_init()
{
    default_scheduler = ex_task_scheduler_create();
    if (default_scheduler == NULL) {
        return EX_FAIL;
    }
    return EX_OK;
}


static void task(ex_task_t task)
{
    uintptr_t num = (uintptr_t) ex_task_get_arg(task);
    EX_LOGD("task:%ld\n", num);
}




int main()
{


#if (EX_TICK_ENABLE==1)


    HANDLE timer;
    DWORD dueTime= 1000;  // 定时器触发的初始延迟时间（在1毫秒后）
    DWORD period= 1000; // 定时器触发的周期（每1毫秒）
        uint32_t flag;

       // 创建一个定时器
    if (!CreateTimerQueueTimer(&timer, NULL, TimerCallback, NULL, dueTime, period,flag)) {
        printf("Failed to create timer\n");
       
    }

#endif

    EX_LOGD("warning0");
    ex_export_init();
    EX_LOGD("warning1");
    
    ex_task_manager_default_init();
    EX_LOGD("warning2");
    ex_timer_config_t config = {.is_periodic = true, .period = 1000};
    ex_task_create_with_scheduler(default_scheduler,_EX_TASK_TYPE_TIMER,task , (void*)1, 1,
                                       &config);

    EX_LOGD("warning3");
    ex_timer_config_t config2 = {.is_periodic = true, .period = 2000};
    ex_task_create_with_scheduler(default_scheduler,_EX_TASK_TYPE_TIMER,task , (void*)2, 1,
    &config2);
     EX_LOGD("warning4");
    ex_task_scheduler_run(default_scheduler);

return 0;

    
}

