/**
 * @file exStddef.h
 * @author ZC (387646983@qq.com)
 * @brief exStddef库
 * @version 0.1
 * @date 2024-11-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _EX_STDDEF_H_
#define _EX_STDDEF_H_



/* ==================== [Includes] ========================================== */

#include "ex_std_cfg.h"

#if EX_STDDEF_IS_ENABLE //当前平台支持标准stddef
    #include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
/* ==================== [Defines] ========================================== */
#if (EX_STDDEF_IS_ENABLE == 0) //当前平台不支持标准stddef

#ifndef NULL
#define NULL ((void *)0)
#endif

#define ptrdiff_t long int   /*!< 指针比较大小类型 */
#define size_t long unsigned int

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Global Prototypes] ========================================== */
#endif // EX_STDDEF_IS_ENABLE


#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EXSTDDEF_H_
