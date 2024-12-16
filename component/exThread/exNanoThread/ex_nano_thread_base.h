#ifndef _EX_NANO_THREAD_H_
#define _EX_NANO_THREAD_H_
/* ==================== [Includes] ========================================== */

#include "../../../exLib/ex_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] ========================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */
typedef struct ex_nano_thread_base{
    ex_list_t *node;
    
}ex_nano_thread_base_t;
/* ==================== [Public Prototypes] ========================================== */

#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EX_NANO_THREAD_H_
