/**
 * @file ex_nano_kernel.c
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-12-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
/* ==================== [Includes] ========================================== */
#include "ex_nano_kernel.h"
#include "ex_nano_scheduler.h"
#include "ex_nano_task.h"
/* ==================== [Defines] ========================================== */
EX_TAG("ex_nano_kernel");
/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ========================================== */

/* ==================== [Static Variables] ========================================== */

/* ==================== [Static Functions] ================================== */


/* ==================== [Public Functions] ================================== */

/**
 * @brief 创建调度器
 * 
 * @param scheduler  调度器对象
 * @param type       调度器类型
 * @param func       任务执行函数
 * @param func_arg  任务参数
 * @param priority  任务优先级
 * @param config    任务配置
 * @return ex_task_t 
 */
ex_task_t ex_task_create_with_scheduler(ex_task_scheduler_t scheduler,ex_task_type_t type,task_cb func,
                                        void* func_arg,uint8_t priority, void *config)
{
    ex_assert(scheduler!=NULL);
    ex_assert(func!=NULL);
    ex_assert(type < _EX_TASK_TYPE_MAX);
    ex_assert(priority < EX_TASK_PRIORITY_LEVELS);
    ex_assert(config!=NULL);
    
    const ex_task_vfunc_t *vfunc = ex_task_get_vfunc(type);
    ex_task_t task=vfunc->create(scheduler,func,func_arg,priority,config);  
}

/**
 * @brief 任务重置
 * 
 * @param task 
 */
void ex_task_reset(ex_task_t task)
{
    ex_assert(task!=NULL);

    ex_task_base_t *handle = (ex_task_base_t *)task;
    handle->vfunc->reset(handle);
}

/**
 * @brief 获取运行任务的参数
 * 
 * @param task 
 * @return void* 
 */
void * ex_task_get_arg(ex_task_t task)
{
    ex_assert(task!=NULL);

    ex_task_base_t *handle = (ex_task_base_t *)task;
    return handle->arg;
}

/**
 * @brief 获取超时时间
 * 
 * @param task 
 * @return int32_t 
 */
int32_t ex_task_get_timeout(ex_task_t task)
{
    ex_assert(task!=NULL);

    ex_task_base_t *task_base = (ex_task_base_t *)task;

    return task_base->timeout;
}

/**
 * @brief 获取调度器句柄
 * 
 * @param task 
 * @return ex_task_scheduler_t 
 */
ex_task_scheduler_t ex_task_get_scheduler(ex_task_t task)
{
    ex_assert(task!=NULL);
    ex_task_base_t *task_base = (ex_task_base_t *)task;

    return task_base->scheduler;
}

/**
 * @brief 任务挂起
 * 
 * @param task 
 * @return ex_err_t -EX_OK
 */
ex_err_t ex_task_suspend(ex_task_t task)
{
    ex_assert(task!=NULL);
    ex_task_base_t *task_base = (ex_task_base_t *)task;
    ex_task_scheduler_t scheduler=task_base->scheduler;

    //删除任务禁止设置挂起
    if (task_base->state == EX_TASK_STATE_DELETE) {
        return EX_ERR_INVALID_STATE;
    }

    ex_task_scheduler_taks_suspend(scheduler, task);
    task_base->suspend_tick = ex_systick_get();

    return EX_OK;
}

/**
 * @brief 任务恢复
 * 
 * @param task 
 * @return ex_err_t -EX_OK
 */
ex_err_t xf_task_resume(ex_task_t task)
{

    ex_assert(task!=NULL);
    ex_task_base_t *task_base = (ex_task_base_t *)task;
    ex_task_scheduler_t scheduler=task_base->scheduler;

    //非挂起任务不允许使用恢复函数
    if (task_base->state != EX_TASK_STATE_SUSPEND) {
        return EX_ERR_INVALID_STATE;
    }

    BITS_SET1(task_base->signal, EX_TASK_SIGNAL_RESUME);

    ex_task_scheduler_set_task_blocked(scheduler, task);

    ex_systick_t resume_time = ex_systick_get() - task_base->suspend_tick; //计算从挂起到恢复的时间

    task_base->wakeup_tick += resume_time; //更新唤醒tick
    
    return EX_OK;
}

/**
 * @brief 任务事件触发唤醒
 * 
 * @param task  唤醒的任务
 * @param arg  任务参数 - 可选，可传递给任务事件
 * @return ex_err_t 
 */
ex_err_t xf_task_trigger(ex_task_t task,void *arg)
{
    ex_assert(task!=NULL);
    ex_task_base_t *handle = (ex_task_base_t *)task;

    BITS_SET1(handle->signal, EX_TASK_SIGNAL_EVENT);

    if (handle->arg != arg) {
        handle->arg = arg;
    }


    return EX_OK;
}

/**
 * @brief 获取任务类型
 * 
 * @param task 
 * @return ex_task_type_t 
 */
ex_task_type_t ex_task_get_type(ex_task_t task)
{
    ex_assert(task!=NULL);
    ex_task_base_t *handle = (ex_task_base_t *)task;

    return (ex_task_type_t)handle->type;
}

/**
 * @brief 获取任务状态
 * 
 * @param task 
 * @return ex_task_state_t 
 */
ex_task_state_t xf_task_get_state(ex_task_t task)
{
    ex_assert(task!=NULL);
    ex_task_base_t *handle = (ex_task_base_t *)task;

    return (ex_task_state_t)handle->state;
}

/**
 * @brief 任务优先级获取
 * 
 * @param task 
 * @return uint8_t 
 */
uint8_t xf_task_get_priority(ex_task_t task)
{
    ex_assert(task!=NULL);

    ex_task_base_t *handle = (ex_task_base_t *)task;

    return (uint8_t)handle->priority;
}

/**
 * @brief 任务优先级设置
 * 
 * @param task 
 * @param priority 
 * @return ex_err_t 
 */
ex_err_t ex_task_set_priority(ex_task_t task, uint16_t priority)
{
    ex_assert(task!=NULL);
    ex_assert(priority < EX_TASK_PRIORITY_LEVELS);

    ex_task_base_t *handle = (ex_task_base_t *)task;

    if (handle->priority != priority) {
        handle->priority = priority;
        // 如果是等待队列中，则修改其所在的优先级队列
        if (handle->state == EX_TASK_STATE_READY) {
            ex_task_scheduler_taks_ready(handle->scheduler, task);
        }
    }

    return EX_OK;
}

/**
 * @brief 任务延时设置
 * 
 * @param task 
 * @param delay_ms 
 * @return ex_err_t 
 */
ex_err_t ex_task_set_delay(ex_task_t task, uint32_t delay_ms)
{
    ex_assert(task!=NULL);
    ex_task_base_t *handle = (ex_task_base_t *)task;

    handle->delay = delay_ms;

    return EX_OK;
}

/**
 * @brief 设置任务函数
 * 
 * @param task 
 * @param func_cb 
 * @param arg 
 * @return ex_err_t 
 */
ex_err_t ex_task_set_func(ex_task_t task,task_cb func_cb,void *arg)
{
    ex_assert(task!=NULL);
    ex_task_base_t *handle = (ex_task_base_t *)task;

    if (handle->task_handler != func_cb) {
        handle->task_handler = func_cb;
    }

    if (handle->arg != arg) {
        handle->arg = arg;
    }

    return EX_OK;
}


