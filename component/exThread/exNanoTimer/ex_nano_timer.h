#ifndef _EX_NANO_TIMER_H_
#define _EX_NANO_TIMER_H_

/* ==================== [Includes] ========================================== */

#include "../../../exLib/ex_lib.h"
#ifdef __cplusplus
extern "C" {
#endif


/* ==================== [Defines] ========================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */
//任务管理器句柄
typedef void *ex_timer_manager_t; 
//定时器回调
typedef void (*ex_timer_callback)(void *arg);

typedef _ex_nano_timer_s{
    ex_list_t list;
    ex_timer_manager_t timer_manager;
    ex_timer_callback callback;
    uint32_t period;
}
/* ==================== [Public Prototypes] ========================================== */

#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EX_NANO_TIMER_H_
