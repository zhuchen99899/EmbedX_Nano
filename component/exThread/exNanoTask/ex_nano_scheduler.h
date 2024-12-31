/**
 * @file ex_nano_scheduler.h
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-12-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _EX_NANO_SCHEDULER_H_
#define _EX_NANO_SCHEDULER_H_



/* ==================== [Includes] ========================================== */
#include "../ex_thread_cfg.h"
#include "../../../exLib/ex_lib.h"
#ifdef __cplusplus
extern "C" {
#endif


/* ==================== [Defines] ========================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */
/**
 * @brief 任务句柄。
 */
typedef void *ex_task_t;

/**
 * @brief 任务调度器句柄。
 * @note 保护任务调度器的 ex_task_scheduler_handle_t数据结构，不对外暴露。仅留出句柄访问。
 */
typedef void *ex_task_scheduler_t;




/* ==================== [Public Prototypes] ========================================== */
ex_task_scheduler_t ex_task_scheduler_create(void);
void ex_task_scheduler_destroy(ex_task_scheduler_t scheduler);
void ex_task_scheduler_run(ex_task_scheduler_t scheduler);
ex_task_t ex_task_scheduler_get_current_task(ex_task_scheduler_t scheduler);
ex_err_t ex_task_scheduler_taks_ready(ex_task_scheduler_t scheduler, ex_task_t task);
ex_err_t ex_task_scheduler_taks_suspend(ex_task_scheduler_t scheduler, ex_task_t task);
ex_err_t ex_task_scheduler_set_task_blocked(ex_task_scheduler_t scheduler, ex_task_t task);
ex_err_t ex_task_scheduler_task_destory(ex_task_scheduler_t schedule,ex_task_t task);

#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EX_NANO_SCHEDULER_H_
