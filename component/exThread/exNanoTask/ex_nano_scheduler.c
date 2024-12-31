/**
 * @file ex_nano_scheduler.c
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-12-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/* ==================== [Includes] ========================================== */
#include "ex_nano_scheduler.h"
#include "ex_nano_kernel.h"
#include "ex_nano_task.h"
/* ==================== [Defines] ========================================== */
EX_TAG("ex_nano_scheduler");
/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

//任务调度器仅在此文件下的成员函数可以被访问 (保护数据结构)
typedef struct _ex_task_sheduler_handle_s{
ex_task_t current_task;                     /*!< 当前任务 */
ex_list_t ready_list[EX_TASK_PRIORITY_LEVELS];/*!< 就绪队列 */
ex_list_t blocked_list;                     /*!< 阻塞队列 */
ex_list_t suspend_list;                     /*!< 挂起队列，挂起主动发起，不参与调度器工作，需要手动唤醒 */
ex_list_t destroy_list;                     /*!< 销毁队列 */

}ex_task_scheduler_handle_t;


/* ==================== [Static Prototypes] ========================================== */

static inline void ex_task_run(ex_task_base_t *task);
static inline void ex_task_update_timeout(ex_task_base_t *task);
/* ==================== [Static Variables] ========================================== */

/* ==================== [Static Functions] ================================== */

/**
 * @brief 运行 task 任务
 * 
 * @param task 
 */
static inline void ex_task_run(ex_task_base_t *task)
{
ex_assert(task != NULL);
ex_task_scheduler_handle_t *scheduler_handle = (ex_task_scheduler_handle_t *)task->scheduler;

ex_list_del_init(&task->node);//从链表队列中删除并重新连接
scheduler_handle->current_task = task;

 
ex_task_update_timeout(task); //更新超时时间
task->vfunc->exec(task->scheduler); //执行任务

scheduler_handle->current_task = NULL;
ex_task_base_set_state(task, EX_TASK_STATE_BLOCKED); //设置为阻塞状态

    // 如果设置成功，则进入阻塞状态。如果设置不成功（删除或挂起）则不管它
    if (task->state == EX_TASK_STATE_BLOCKED) {
        ex_list_add_tail(&task->node, &scheduler_handle->blocked_list);
    }
}

static inline void ex_task_update_timeout(ex_task_base_t *task)
{
    ex_systick_t timeout = ex_systick_get()-task->wakeup_tick;
    task->timeout= ex_task_ticks_to_msec(timeout); //换算为毫秒

}

/* ==================== [Public Functions] ================================== */

/**
 * @brief 创建任务调度器
 * 
 * @return ex_task_scheduler_t 
 */
ex_task_scheduler_t ex_task_scheduler_create(void){
    ex_task_scheduler_handle_t *sheduler = ex_malloc(sizeof(ex_task_scheduler_handle_t));
    ex_assert(sheduler != NULL);

    sheduler->current_task = NULL;
      for (size_t i = 0; i < EX_TASK_PRIORITY_LEVELS; i++) {
        ex_list_init(&sheduler->ready_list[i]);
    }
    
    ex_list_init(&sheduler->destroy_list);
    ex_list_init(&sheduler->blocked_list);
    ex_list_init(&sheduler->suspend_list);

    return (ex_task_scheduler_t)sheduler;
}

/**销毁任务调度器 */
void ex_task_scheduler_destroy(ex_task_scheduler_t scheduler){
    ex_assert(scheduler != NULL);
    ex_free(scheduler);
}




void ex_task_scheduler_run(ex_task_scheduler_t scheduler){
    ex_assert(scheduler != NULL);
    ex_task_scheduler_handle_t* scheduler_handle = (ex_task_scheduler_handle_t *)scheduler;


    volatile uint32_t index = 0; //就绪队列目录
    volatile bool is_get_func = false; //当前有就绪任务

     ex_task_base_t *task, *_task; //迭代对象 缓存指针
    while(1)
    {

        
        /*阻塞队列任务处理 */
        is_get_func = false;
        ex_list_for_each_entry_safe(task,_task,&scheduler_handle->blocked_list,ex_task_base_t,node){

            uint32_t timetick = task->vfunc->update(task); //更新任务信号
            if (BITS_CHECK(task->signal, EX_TASK_SIGNAL_READY)) {
                ex_list_del_init(&task->node);
      
                ex_task_base_set_state(task, EX_TASK_STATE_READY); // 设置为就绪态
                ex_list_add_tail(&task->node, &scheduler_handle->ready_list[task->priority]);
                BITS_SET0(task->signal, EX_TASK_SIGNAL_READY);
                }
        

            if (task->delay == 0 || task->timeout > 0 || task->state != EX_TASK_STATE_BLOCKED) {
            continue;//当前任务需要触发
            }
        
        }//iterate blocked list

        // 就绪任务队列处理
        // 这里决定了它的优先级数值越小优先级越高
        for (index = 0; index < EX_TASK_PRIORITY_LEVELS; index++) {
            if (ex_list_empty(&scheduler_handle->ready_list[index])) {
                continue; //跳过空表
            }
            // 选取相对最高优先级的任务作为执行任务
            if (false == is_get_func) {
                task = ex_list_first_entry(&scheduler_handle->ready_list[index],ex_task_base_t,node);
                ex_task_run(task);
                is_get_func = true;
                break;
            }
        }

        // 上述循环正常退出，则说明没有就绪任务，运行空闲任务
        if (false == is_get_func) {
            // 空闲时间，处理一下需要删除的任务
            ex_list_for_each_entry_safe(task, _task, &scheduler_handle->destroy_list, ex_task_base_t, node) {
                ex_list_del_init(&task->node);
                task->delete(task);
            }

            // 执行空闲回调
            //EX_LOGD("IDLE");
        }

    }//while
}


/**
 * @brief 获取当前任务
 * 
 * @param scheduler 
 * @return ex_task_t 
 */
ex_task_t ex_task_scheduler_get_current_task(ex_task_scheduler_t scheduler){
    ex_assert(scheduler != NULL);
    ex_task_scheduler_handle_t *scheduler_handle = (ex_task_scheduler_handle_t *)scheduler;
    return scheduler_handle->current_task;
}


/**
 * @brief 设置任务为就绪态
 * 
 * @param scheduler 
 * @param task 
 * @return ex_err_t  -EX_OK
 */
ex_err_t ex_task_scheduler_taks_ready(ex_task_scheduler_t scheduler, ex_task_t task){
    ex_assert(scheduler != NULL);
    ex_assert(task != NULL);

    ex_task_scheduler_handle_t *scheduler_handle = (ex_task_scheduler_handle_t *)scheduler;

    ex_task_base_t * task_base = (ex_task_base_t *)task;

    ex_list_del_init(&task_base->node);//从链表队列中删除并重新连接
    ex_task_base_set_state(task, EX_TASK_STATE_READY); //设置为就绪状态
    ex_list_add_tail(&task_base->node, &scheduler_handle->ready_list[task_base->priority]); //加入链表尾端

    return EX_OK;
}

/**
 * @brief 设置任务为挂起，挂起后需要手动唤醒才能参与任务调度
 * 
 * @param scheduler 
 * @param task 
 * @return ex_err_t  -EX_OK
 */
ex_err_t ex_task_scheduler_taks_suspend(ex_task_scheduler_t scheduler, ex_task_t task){
    ex_assert(scheduler != NULL);
    ex_assert(task != NULL);

    ex_task_scheduler_handle_t *scheduler_handle = (ex_task_scheduler_handle_t *)scheduler;

    ex_task_base_t * task_base = (ex_task_base_t *)task;

    ex_list_del_init(&task_base->node);//从链表队列中删除并重新连接

    ex_task_base_set_state(task, EX_TASK_STATE_SUSPEND); //设置为挂起状态
    ex_list_add_tail(&task_base->node, &scheduler_handle->suspend_list); //加入链表尾端

    return EX_OK;
}

/**
 * @brief 设置任务阻塞 ，阻塞后任务不会参与调度，直到被唤醒
 * 
 * @param scheduler 
 * @param task 
 * @return ex_err_t  -EX_OK
 */
ex_err_t ex_task_scheduler_set_task_blocked(ex_task_scheduler_t scheduler, ex_task_t task){
    ex_assert(scheduler != NULL);
    ex_assert(task != NULL);

    ex_task_scheduler_handle_t *scheduler_handle = (ex_task_scheduler_handle_t *)scheduler;

    ex_task_base_t * task_base = (ex_task_base_t *)task;

    ex_list_del_init(&task_base->node); //从链表队列中删除并重新连接

    ex_task_base_set_state(task ,EX_TASK_STATE_BLOCKED);//设置为阻塞状态

    ex_list_add_tail(&task_base->node, &scheduler_handle->blocked_list); //加入链表尾端
    return EX_OK;
}


/**
 * @brief 调度器删除任务
 * 
 * @param schedule 
 * @param task 
 * @return ex_err_t -EX_OK
 */
ex_err_t ex_task_scheduler_task_destory(ex_task_scheduler_t schedule,ex_task_t task){
ex_assert(schedule != NULL);
ex_assert(task != NULL);


ex_task_scheduler_handle_t *scheduler_handle = (ex_task_scheduler_handle_t *)schedule;
ex_task_base_t *task_base = (ex_task_base_t *)task;

ex_list_del_init(&task_base->node); //从链表队列中删除并重新连接
ex_task_base_set_state(task, EX_TASK_STATE_DELETE); //设置为删除状态
ex_list_add_tail(&task_base->node, &scheduler_handle->destroy_list); //加入链表尾端


return EX_OK;
}