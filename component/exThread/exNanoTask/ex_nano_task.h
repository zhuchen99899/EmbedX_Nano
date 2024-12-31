/**
 * @file ex_nano_task.h
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-12-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _EX_NANO_TASK_H_
#define _EX_NANO_TASK_H_



/* ==================== [Includes] ========================================== */

#include "../../../exLib/ex_lib.h"
#include "ex_nano_scheduler.h"
#ifdef __cplusplus
extern "C" {
#endif


/* ==================== [Defines] ========================================== */
/**
 * @name EX_TASK_SIGNAL
 * @brief 内部传递消息使用，外部无法设置。
 * @{
 */
#define EX_TASK_SIGNAL_READY            (1UL << 0)  /*!< 准备信号，通知调度器该任务可进入就绪 */
#define EX_TASK_SIGNAL_TIMEOUT          (1UL << 1)  /*!< 超时信号，会在任务更新中转变为准备信号 */
#define EX_TASK_SIGNAL_EVENT            (1UL << 2)  /*!< 事件信号，会在任务更新中转变为准备信号 */
#define EX_TASK_SIGNAL_RESUME           (1UL << 3)  /*!< 恢复信号，通知任务从挂起状态被恢复 */
/**
/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

typedef enum _ex_task_state_e{
    EX_TASK_STATE_READY = 0,    /*!< 就绪状态 */
    EX_TASK_STATE_RUNNING,      /*!< 运行状态 */
    EX_TASK_STATE_BLOCKED,      /*!< 阻塞状态 */
    EX_TASK_STATE_SUSPEND,      /*!< 挂起状态 */
    EX_TASK_STATE_DELETE       /*!< 删除状态 */
}ex_task_state_t; //任务状态



/**
 * @brief 构造任务函数指针，函数对象由它构造。
 *
 * @param manager 任务所从属的任务管理器。
 * @param func  任务执行的函数。
 * @param func_arg 任务用户定义的参数。
 * @param priority 任务优先级。
 * @param config 任务参数配置（不同任务配置不同）。
 * @return ex_task_t 返回 NULL 则表示任务构造失败，构造成功则返回任务对象
 */
typedef ex_task_t (*ex_task_create_t)(ex_task_scheduler_t manager, ex_task_t func, void *func_arg, uint8_t priority,
                                      void *config);

/**
 * @brief 删除任务函数指针。函数对象的生命周期结尾时调用。
 *
 * @param task 任务对象。
 */
typedef void (*ex_task_delete_t)(ex_task_t task);

/**
 * @brief 重置任务函数指针，重置任务的状态
 *
 * @param task 任务对象。
 */
typedef void (*ex_task_reset_t)(ex_task_t task);

/**
 * @brief 任务更新函数。当任务出于阻塞状态时运行，更新当前任务状态。
 *
 * @param task 任务对象。
 * @return ex_task_time_t 当前更新参考的时间戳
 */
typedef ex_systick_t (*ex_task_update_t)(ex_task_t task);

/**
 * @brief 任务执行函数。调度器用于恢复/执行当前任务。
 *
 * @param scheduler 任务管理器对象。
 */
typedef void(*ex_task_exec_t)(ex_task_scheduler_t scheduler);


typedef struct _ex_task_virtualFunction_s {
   const ex_task_create_t create;  /*!< 创建任务 */
   const ex_task_reset_t reset;   /*!<重置任务*/
   const ex_task_update_t update; /*< 更新任务状态 */
   const ex_task_exec_t exec;     /*!< 执行任务 */
}ex_task_vfunc_t;

/**
 * @brief 任务回调函数
 * 
 */
typedef void (*task_cb)(void *arg);

/**
 * @brief 任务基类
 * 
 */
typedef struct _ex_task_base_s{

    ex_list_t node;           /*!< 链表节点 */
    ex_task_scheduler_t scheduler; /*!< 任务调度器 */
    uint32_t enabled:1;                /*!< 使能 */
    uint32_t auto_reload:1;            /*!< 自动重装 */
    uint32_t type:1;                   /*!< 任务类型 */
    uint32_t state:4;                  /*!< 任务状态 */
    uint32_t signal:8;                 /*!< 任务信号 */
    uint32_t priority:8;               /*!< 优先级 */
    uint32_t reserved:9;              /*!< 保留 */
    uint32_t delay;          /*!< timer:调度周期  携程:延时时间 用户设置*/
    uint32_t timeout;        /*!< 超时时间 ,配合调度,非用户设置*/
    ex_systick_t wakeup_tick; /*!< 唤醒时间 系统时钟*/
    ex_systick_t suspend_tick; /*!< 挂起时间 系统时钟*/
    task_cb task_handler;   /*!< 任务回调函数 */
    ex_task_delete_t delete; /*!< 删除任务函数 */
    const ex_task_vfunc_t *vfunc; /*!< 虚函数表 */
    void *arg;              /*!< 任务参数 ,回调函数参数*/ 
}ex_task_base_t;




/* ==================== [Public Prototypes] ========================================== */

ex_err_t ex_task_vfunc_register(ex_task_type_t type, const ex_task_vfunc_t *vfunc);
ex_err_t ex_task_vfunc_unregister(ex_task_type_t type);
const ex_task_vfunc_t *ex_task_get_vfunc(ex_task_type_t type);



void ex_task_base_init(ex_task_base_t *task_father,ex_task_scheduler_t scheduler,ex_task_type_t type,
                        uint16_t priority,task_cb func,void  *arg);
void ex_task_base_reset(ex_task_base_t *task_father);
ex_err_t ex_task_base_set_state(ex_task_t task,ex_task_state_t state);
void ex_task_destroy(ex_task_t task);

#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EX_NANO_TASK_H_
