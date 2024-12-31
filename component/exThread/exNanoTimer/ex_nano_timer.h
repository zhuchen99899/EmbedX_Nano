#ifndef _EX_NANO_TIMER_H_
#define _EX_NANO_TIMER_H_

/* ==================== [Includes] ========================================== */

#include "../../../exLib/ex_lib.h"
<<<<<<< HEAD
#include "../exNanoTask/ex_nano_task.h"
#include "../../exExport/ex_export.h"
=======
>>>>>>> 0fca154d92f7a51196736ed04f9fcbf854183da0
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

<<<<<<< HEAD

typedef struct _ex_timer_config_s{
    bool is_periodic; //是否周期性
    uint32_t period; //周期
}ex_timer_config_t;



=======
typedef _ex_nano_timer_s{
    ex_list_t list;
    ex_timer_manager_t timer_manager;
    ex_timer_callback callback;
    uint32_t period;
}
>>>>>>> 0fca154d92f7a51196736ed04f9fcbf854183da0
/* ==================== [Public Prototypes] ========================================== */

#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EX_NANO_TIMER_H_
