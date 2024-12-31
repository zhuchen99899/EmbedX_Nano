#ifndef _EX_NANO_TIMER_H_
#define _EX_NANO_TIMER_H_

/* ==================== [Includes] ========================================== */

#include "../../../exLib/ex_lib.h"
#include "../exNanoTask/ex_nano_task.h"
#include "../../exExport/ex_export.h"
#ifdef __cplusplus
extern "C" {
#endif


/* ==================== [Defines] ========================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */


typedef struct _ex_timer_config_s{
    bool is_periodic; //是否周期性
    uint32_t period; //周期
}ex_timer_config_t;



/* ==================== [Public Prototypes] ========================================== */

#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EX_NANO_TIMER_H_
