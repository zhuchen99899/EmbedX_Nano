/**
 * @file cmsis_os2.c
 * @author ZC (387646983@qq.com)
 * @brief cmsis_os2 操作系统抽象层实现
 * @version 0.1
 * @date 2024-12-08
 * @note 使用cmsis_os2 api 可跨平台兼容EmbedX_Nano 中的device组件 以及timer组件
 * @copyright Copyright (c) 2024
 * 
 */

#include "../../exLib/ex_lib.h"
#include "exNanoMutex/ex_nano_mutex.h"
#include "exNanoSemaphore/ex_nano_sem.h"
#include "cmsis_os2.h"
EX_TAG("CMSIS_OS2");

/* ==================== [Includes] ========================================== */

/* ==================== [Defines] ========================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ========================================== */

/* ==================== [Static Variables] ========================================== */

/* ==================== [Static Functions] ================================== */

/* ==================== [Public Functions] ================================== */

/*互斥锁 */
osMutexId_t osMutexNew (const osMutexAttr_t *attr)
{
    
    ex_assert(attr != NULL);
    (void)attr;
    ex_nano_mutex_t *mutex =ex_malloc(sizeof(ex_nano_mutex_t));
    ex_assert(mutex != NULL);
    EX_MUTEX_CREATE(mutex,attr->name);
    return (osMutexId_t)mutex;
}


osStatus_t osMutexAcquire (osMutexId_t mutex_id, uint32_t timeout)
{
    uint32_t elapsed = 0;
    ex_assert(mutex_id != NULL);
    ex_assert(timeout == osWaitForever);
    ex_nano_mutex_t *mutex = (ex_nano_mutex_t *)mutex_id;
    ex_assert(mutex->name!=NULL);
    
    while (mutex->lock == true)
    {
            if (elapsed >= timeout) {
                EX_LOGE("osErrorTimeout");
            }
            elapsed++;
    }
    if (mutex->lock == false)
    {
        EX_MUTEX_LOCK(mutex);
        return osOK;

    }
    else{
        return osError;

    }
}

osStatus_t osMutexRelease (osMutexId_t mutex_id)
{
    
    ex_assert(mutex_id != NULL);
    ex_nano_mutex_t *mutex = (ex_nano_mutex_t *)mutex_id;
    if(mutex->lock == false){
        return osError;
    }
    else{
    EX_MUTEX_UNLOCK(mutex);
    return osOK;
    }

}

osStatus_t osMutexDelete (osMutexId_t mutex_id)
{
    ex_assert(mutex_id != NULL);
    ex_nano_mutex_t *mutex = (ex_nano_mutex_t *)mutex_id;
    EX_MUTEX_DELETE(mutex);
    ex_free(mutex);

    return osOK;
}


/*信号量 */

osSemaphoreId_t osSemaphoreNew (uint32_t max_count, uint32_t initial_count, const osSemaphoreAttr_t *attr)
{
    ex_assert(initial_count <= max_count);
    
    ex_nano_sem_t *sem =ex_malloc(sizeof(ex_nano_sem_t));
    if(attr == NULL)
    {
       EX_SEMAPHORE_CREATE(sem,NULL,initial_count,max_count); 
    }
    else{
        EX_SEMAPHORE_CREATE(sem,attr->name,initial_count,max_count);
    }


    return (osSemaphoreId_t)sem;
}

osStatus_t osSemaphoreAcquire (osSemaphoreId_t semaphore_id, uint32_t timeout)
{
    ex_assert(semaphore_id != NULL);
    ex_nano_sem_t *sem = (ex_nano_sem_t *)semaphore_id;
    uint32_t elapsed = 0;
    while(sem->count == 0)
    {
        if (elapsed >= timeout) {
            EX_LOGE("osErrorTimeout");
        }
        elapsed++;
    }
    if(sem->count > 0)
    {
        EX_SEMAPHORE_ACQUIRE(sem);
        return osOK;
    }

    return osError;
    
}

osStatus_t osSemaphoreRelease (osSemaphoreId_t semaphore_id)
{

    ex_assert(semaphore_id != NULL);
    ex_nano_sem_t *sem = (ex_nano_sem_t *)semaphore_id;

    if (sem->count < sem->max_count) { // 释放信号量时检查是否超出最大计数
        EX_SEMAPHORE_SIGNAL(sem); // 释放信号量（增计数）
        return osOK;
    }

    return osErrorResource; // 超出最大计数返回错误
}

osStatus_t osSemaphoreDelete (osSemaphoreId_t semaphore_id)
{
    ex_assert(semaphore_id != NULL);
    ex_nano_sem_t *sem = (ex_nano_sem_t *)semaphore_id;
    EX_SEMAPHORE_DELETE(sem);
    ex_free(sem);
    return osOK;
}
