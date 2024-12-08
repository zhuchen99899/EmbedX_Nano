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
/**创建互斥锁 */
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
                return osErrorTimeout;
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