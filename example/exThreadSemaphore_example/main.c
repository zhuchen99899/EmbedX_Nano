
#include "../../component/exThread/ex_thread.h"
#include "../../exLib/ex_lib.h"
EX_TAG("MAIN");

void main(void)
{
   
    while(1){        
       

    //获取信号量
     osSemaphoreId_t sem=osSemaphoreNew(2, 2, NULL);
    if (osSemaphoreAcquire(sem, osWaitForever) == osOK) {
        EX_LOGD("Semaphore acquired.\n");

        // 使用共享资源

        // 释放信号量
        osSemaphoreRelease(sem);
    } else {
        EX_LOGD("Failed to acquire semaphore.\n");
    }

    // 删除信号量
    osSemaphoreDelete(sem);

    }
}