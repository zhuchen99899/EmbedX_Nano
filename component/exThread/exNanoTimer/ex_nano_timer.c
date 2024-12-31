/**
 * @file ex_nano_timer.c
 * @author ZC (387646983@qq.com)
 * @brief exNanoTimer
 * @version 0.1
 * @date 2024-12-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
/* ==================== [Includes] ========================================== */
#include "ex_nano_timer.h"

/* ==================== [Defines] ========================================== */
EX_TAG("ex_nano_timer");
/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */
typedef struct _exTimer_s
{
    ex_task_base_t base;                     /*!< 父类 */
}ex_timer_t;
/* ==================== [Static Prototypes] ========================================== */

static ex_task_t _ex_timer_create(ex_task_scheduler_t scheduler, ex_task_t func, void *func_arg, uint8_t priority,void *config);
static void _ex_timer_reset(ex_task_t task);
static ex_systick_t _ex_timer_update(ex_task_t task);
static void _ex_timer_exec(ex_task_scheduler_t scheduler);
/* ==================== [Static Variables] ========================================== */


static const ex_task_vfunc_t _ex_timer_vfunc = {
    .create = _ex_timer_create,
    .reset = _ex_timer_reset,
    .update = _ex_timer_update,
    .exec = _ex_timer_exec,
};

void ex_vfunc_register(void)
{
    ex_task_vfunc_register(_EX_TASK_TYPE_TIMER, &_ex_timer_vfunc);
}
EX_INIT_EXPORT(ex_vfunc_register,EXPORT_LEVEL_COMPONENT);

/* ==================== [Static Functions] ================================== */
static ex_task_t _ex_timer_create(ex_task_scheduler_t scheduler, ex_task_t func, void *func_arg, uint8_t priority,void *config)
{
    ex_timer_t *timer = (ex_timer_t *)ex_malloc(sizeof(ex_timer_t));
    
    if(timer == NULL)
    {
        EX_LOGE("timer create failed");
        return NULL;
    }

    ex_timer_config_t *timer_config = config;
    
    uint32_t ticks=ex_task_msec_to_ticks(timer_config->period);

    ex_task_base_init(&timer->base, scheduler, _EX_TASK_TYPE_TIMER, priority, func, func_arg);


    timer->base.delay = ticks;
    timer->base.auto_reload=timer_config->is_periodic;


    timer->base.wakeup_tick = ex_systick_get() + ticks;

    return (ex_task_t)timer;
}


static void _ex_timer_reset(ex_task_t task)
{
    ex_timer_t *timer=(ex_timer_t *)task;
    ex_task_base_reset(&timer->base);

}

/**
 * @brief 周期性定时处理
 * 
 * @param task 
 * @param time_ticks 
 */
static void ex_timer_task_handle(ex_task_t task,uint32_t time_ticks)
{
    ex_timer_t *timer = (ex_timer_t *)task;
    int32_t timeout= time_ticks-timer->base.wakeup_tick;

    timer->base.timeout =ex_task_ticks_to_msec(timeout);


    // EX_LOGW("tick:%d",time_ticks);
    // EX_LOGI("timer->base.wakeup_tick:%d",timer->base.wakeup_tick);
 
    if(timeout>=0)
    {

    BITS_SET1(timer->base.signal, EX_TASK_SIGNAL_TIMEOUT);

    }
}


/**
 * @brief 定时器任务状态更新
 * 
 * @param task 
 * @return ex_systick_t 
 */
static ex_systick_t _ex_timer_update(ex_task_t task)
{
    ex_timer_t *timer = (ex_timer_t *)task;
    ex_systick_t tick = ex_systick_get();
    // EX_LOGW("tick:%d",tick);
    // EX_LOGI("timer->base.wakeup_tick:%d",timer->base.wakeup_tick);
    if(timer->base.delay!=0) //周期性任务
    {
        ex_timer_task_handle(timer,tick);
    }

   
    if (BITS_CHECK(timer->base.signal, EX_TASK_SIGNAL_TIMEOUT)) { //超时触发

        BITS_SET0(timer->base.signal, EX_TASK_SIGNAL_TIMEOUT);
        BITS_SET1(timer->base.signal, EX_TASK_SIGNAL_READY);
    }

    if (BITS_CHECK(timer->base.signal, EX_TASK_SIGNAL_EVENT)) { //事件触发
        BITS_SET0(timer->base.signal, EX_TASK_SIGNAL_EVENT);
        BITS_SET1(timer->base.signal, EX_TASK_SIGNAL_READY);
    }

    return tick;
}




/**
 * @brief 定时器任务执行
 * 
 * @param scheduler 
 */
static void _ex_timer_exec(ex_task_scheduler_t scheduler)
{
    ex_timer_t *timer = (ex_timer_t *)ex_task_scheduler_get_current_task(scheduler);


    ex_task_base_set_state(timer,EX_TASK_STATE_RUNNING);
    timer->base.task_handler(timer);

    if(timer->base.delay!=0)
    {
        
        timer->base.wakeup_tick = ex_systick_get() + timer->base.delay;
    }

}

/* 

/* ==================== [Public Functions] ================================== */



/* ==================== [End] ================================== */