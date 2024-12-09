/**
 * @file ex_nano_sem.h
 * @author ZC (387646983@qq.com)
 * @brief 信号量
 * @version 0.1
 * @date 2024-12-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _EX_NANO_SEM_H_
#define _EX_NANO_SEM_H_


#include "../../../exLib/ex_lib.h"


/* ==================== [Includes] ========================================== */


#ifdef __cplusplus
extern "C" {
#endif


/* ==================== [Defines] ========================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

// 定义信号量结构体
typedef struct ex_nano_semaphore {
    int32_t count;          // 信号量当前计数值
    int32_t max_count;      // 信号量最大计数值
    const char* name;       // 信号量名称
} ex_nano_sem_t;
/* ==================== [Public Prototypes] ========================================== */

// 信号量操作
// 信号量操作
#define EX_SEMAPHORE_CREATE(_sem, _name, _initial_count, _max_count) \
    do { \
        (_sem)->count = (_initial_count); \
        (_sem)->max_count = (_max_count); \
        (_sem)->name = (_name); \
    } while (0)

#define EX_SEMAPHORE_ACQUIRE(_sem) \
    do { \
        (_sem)->count--; \
    } while (0)

#define EX_SEMAPHORE_SIGNAL(_sem) \
    do { \
            (_sem)->count++; \
    } while (0)

#define EX_SEMAPHORE_DELETE(_sem) \
    do { \
        (_sem)->count = 0; \
        (_sem)->max_count = 0; \
        (_sem)->name = NULL; \
    } while (0)

#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EX_NANO_SEM_H_
