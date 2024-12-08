/**
 * @file ex_nano_mutex.h
 * @author ZC (387646983@qq.com)
 * @brief exThread 互斥锁
 * @version 0.1
 * @date 2024-12-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _EX_NANO_MUTEX_H_
#define _EX_NANO_MUTEX_H_



/* ==================== [Includes] ========================================== */

#include "../../../exLib/ex_lib.h"

#ifdef __cplusplus
extern "C" {
#endif



// 定义互斥锁结构体
typedef struct ex_nano_mutex {
    bool lock;              // 互斥锁状态
    const char* name;       // 互斥锁名称
} ex_nano_mutex_t;

// 互斥锁操作
#define EX_MUTEX_CREATE(_mutex, _name) \
    do { \
        (_mutex)->lock = false; \
        (_mutex)->name = (_name); \
    } while (0)

#define EX_MUTEX_LOCK(_mutex) \
    do { \
        (_mutex)->lock = true; \
    } while (0)

#define EX_MUTEX_UNLOCK(_mutex) \
    do { \
        (_mutex)->lock = false; \
    } while (0)

#define EX_MUTEX_DELETE(_mutex) \
    do { \
        (_mutex)->lock = false; \
        (_mutex)->name = NULL; \
    } while (0)


/* ==================== [Defines] ========================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Public Prototypes] ========================================== */

#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EX_NANO_MUTEX_H_





