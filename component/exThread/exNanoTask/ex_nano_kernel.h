#ifndef _EX_NANO_KERNEL_H_
#define _EX_NANO_KERNEL_H_



/* ==================== [Includes] ========================================== */
#include "ex_nano_scheduler.h"
#include "ex_nano_task.h"
#ifdef __cplusplus
extern "C" {
#endif


/* ==================== [Defines] ========================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */


/* ==================== [Public Prototypes] ========================================== */


ex_task_t ex_task_create_with_scheduler(ex_task_scheduler_t scheduler,ex_task_type_t type,task_cb func,
                                        void* func_arg,uint8_t priority, void *config);



void ex_task_reset(ex_task_t task);

void * ex_task_get_arg(ex_task_t task);

int32_t ex_task_get_timeout(ex_task_t task);

ex_task_scheduler_t ex_task_get_scheduler(ex_task_t task);

ex_err_t ex_task_suspend(ex_task_t task);

ex_err_t xf_task_resume(ex_task_t task);


ex_err_t xf_task_trigger(ex_task_t task,void *arg);

ex_task_type_t ex_task_get_type(ex_task_t task);

ex_task_state_t xf_task_get_state(ex_task_t task);


uint8_t xf_task_get_priority(ex_task_t task);

ex_err_t ex_task_set_priority(ex_task_t task, uint16_t priority);

ex_err_t ex_task_set_delay(ex_task_t task, uint32_t delay_ms);

ex_err_t ex_task_set_func(ex_task_t task,task_cb func_cb,void *arg);


#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EX_NANO_KERNEL_H_
