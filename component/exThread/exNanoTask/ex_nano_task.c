/**
 * @file ex_nano_task.c
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-12-24
 * @note nano_task
 * @copyright Copyright (c) 2024
 * 
 */

/* ==================== [Includes] ========================================== */
#include "ex_nano_task.h"
/* ==================== [Defines] ========================================== */
EX_TAG("ex_nano_task");
/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ========================================== */

/* ==================== [Static Variables] ========================================== */
static const ex_task_vfunc_t *_ex_task_vfunc_group[_EX_TASK_TYPE_MAX] = {0};
/* ==================== [Static Functions] ================================== */

/* ==================== [Public Functions] ================================== */
/**
 * @brief 注册虚函数
 * 
 * @param type      注册任务类型
 * @param vfunc     待注册虚函数
 * @return ex_err_t 
 */
ex_err_t ex_task_vfunc_register(ex_task_type_t type, const ex_task_vfunc_t *vfunc)
{
    ex_assert(type<_EX_TASK_TYPE_MAX);

    _ex_task_vfunc_group[type] = vfunc; //虚函数表

    return EX_OK;
}

/**
 * @brief 注销虚函数
 * 
 * @param type      注册任务类型
 * @return ex_err_t  EX_OK 注销成功
 */
ex_err_t ex_task_vfunc_unregister(ex_task_type_t type)
{
    ex_assert(type<_EX_TASK_TYPE_MAX);
    ex_assert(_ex_task_vfunc_group[type]!=NULL);

    _ex_task_vfunc_group[type] = NULL;  

    return EX_OK;

}

/**
 * @brief 获取虚函数表
 * 
 * @param type 
 * @return const ex_task_vfunc_t* 
 */
const ex_task_vfunc_t *ex_task_get_vfunc(ex_task_type_t type)
{
    ex_assert(type < _EX_TASK_TYPE_MAX);
    ex_assert(_ex_task_vfunc_group[type]!=NULL);

    return _ex_task_vfunc_group[type];
}


/**
 * @brief  注册任务基类
 * 
 * @param task_father  任务对象基类
 * @param scheduler     任务调度器句柄
 * @param type          任务类型
 * @param priority      任务优先级
 * @param func          任务执行函数
 * @param arg           任务参数
 */
void ex_task_base_init(ex_task_base_t *task_father,ex_task_scheduler_t scheduler,ex_task_type_t type,
                        uint16_t priority,task_cb func,void  *arg)
{

    
    task_father->scheduler = scheduler;
    task_father->task_handler = func;
    task_father->type = type;
    task_father->priority = priority;
    task_father->arg = arg;

    task_father->enabled=0; //默认不启动任务
    task_father->auto_reload=1; //默认自动重装载
    task_father->signal=0x00; //默认无信号
    task_father->reserved=0; //默认保留
    task_father->state=EX_TASK_STATE_BLOCKED; //默认阻塞状态
    task_father->delay=0; //默认周期0
    task_father->timeout=0; //默认超时时间

    task_father->suspend_tick=ex_systick_get(); //默认挂起时间
    task_father->wakeup_tick=ex_systick_get(); //默认唤醒时间

    task_father->vfunc = _ex_task_vfunc_group[type];
    task_father->delete = ex_task_destroy;
    ex_list_init(&task_father->node);

    ex_task_scheduler_set_task_blocked(scheduler,task_father);
}

void ex_task_base_reset(ex_task_base_t *task_father)
{
    ex_assert(task_father!=NULL);

    task_father->state = EX_TASK_STATE_BLOCKED;
    task_father->signal = 0;
    task_father->wakeup_tick = 0;
    task_father->suspend_tick = 0;
    task_father->timeout = 0;
    ex_list_del_init(&task_father->node);
    ex_task_scheduler_set_task_blocked(task_father->scheduler, task_father);
    
}


/**
 * @brief 设置任务状态
 * 
 * @param task 
 * @param state 
 * @return ex_err_t  - EX_ERR_NOT_SUPPORT 当任务出于删除态或者挂起态，此时设置状态无用
 *                   - XF_OK 设置成功
 */
ex_err_t ex_task_base_set_state(ex_task_t task,ex_task_state_t state)
{
    ex_task_base_t *task_base = (ex_task_base_t *)task;

    if (task_base->state == EX_TASK_STATE_DELETE) { //任务处于删除态
        EX_LOGD("task will be delete");
        return EX_ERR_NOT_SUPPORT;
    }

    if(task_base->state==EX_TASK_STATE_SUSPEND) //任务处于挂起状态
    {
        //处于挂起状态切换任务的状态 必须有恢复信号
       if(BITS_CHECK(task_base->signal,EX_TASK_SIGNAL_RESUME)) //恢复信号
       {
           BITS_SET0(task_base->signal,EX_TASK_SIGNAL_RESUME);
       }
       else
       {
        EX_LOGD( "task was suspend");
        return EX_ERR_NOT_SUPPORT;
       }

    }

    task_base->state = state;

    return EX_OK;
}


/**
 * @brief 任务销毁
 * 
 * @param task 
 */
void ex_task_destroy(ex_task_t task)
{   
    ex_task_base_t *task_base = (ex_task_base_t *)task;
    ex_free(task);
    EX_LOGD("task destroy");
}