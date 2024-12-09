
#include "../../component/exThread/ex_thread.h"
#include "../../exLib/ex_lib.h"
EX_TAG("MAIN");

static osMutexAttr_t mutexAttr = {
    .name = "MyMutex",
    .attr_bits = 0,
    .cb_mem = NULL,
    .cb_size = 0
};

 void main(int argc, char *argv[]) {
 
    // 创建互斥锁
    osMutexId_t myMutex  = osMutexNew(&mutexAttr);

    while(1)
    {

//EXAMPLE1

    // 获取互斥锁
    osStatus_t ret=osMutexAcquire(myMutex, osWaitForever);

    if (ret == osOK) {
        EX_LOGD("Mutex acquired successfully.\n");
    }
    else {
        EX_LOGD("Failed to acquire mutex. \n");
    }

    // 释放互斥锁
    osStatus_t ret2=osMutexRelease(myMutex);

    if (ret2 == osOK) {
        EX_LOGD("Mutex released successfully.\n");    
    } else {
        EX_LOGD("Failed to release mutex.\n");
    }

//EXAMPLE2
    // 获取互斥锁
    ret=osMutexAcquire(myMutex, osWaitForever);

    if (ret == osOK) {
        EX_LOGD("Mutex acquired successfully.\n");
    }
    else {
        EX_LOGD("Failed to acquire mutex. \n");
    }
    // 获取互斥锁后再次获取互斥锁造成阻塞
    ret=osMutexAcquire(myMutex, osWaitForever);

    if (ret == osOK) {
        EX_LOGD("Mutex acquired successfully.\n");
    }
    else {
        EX_LOGD("Failed to acquire mutex. \n");
    }


//EXAMPLE3
    // 删除互斥锁
    if (osMutexDelete(myMutex) == osOK) {
        EX_LOGD("Mutex deleted successfully.\n");
    } else {
        EX_LOGD("Failed to delete mutex.\n");
    }

    }
 }
