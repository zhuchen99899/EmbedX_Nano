/**
 * @file ex_nano_thread_base.h
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-12-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _EX_NANO_THREAD_BASE_H_
#define _EX_NANO_THREAD_BASE_H_



/* ==================== [Includes] ========================================== */
#include "../../../exLib/ex_lib.h"
#include "ex_nano_thread_manager.h"
#ifdef __cplusplus
extern "C" {
#endif


/* ==================== [Defines] ========================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */
typedef struct ex_nano_thread_base{
    ex_list_t node;
    ex_task_manager_t manager;
    ex_task_func_t func;
}ex_nano_thread_base_t;
/* ==================== [Public Prototypes] ========================================== */

#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EX_NANO_THREAD_BASE_H_
