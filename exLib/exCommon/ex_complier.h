/**
 * @file ex_complier.h
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-11-28
 * @note 编译器相关功能
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _EX_COMPLIER_H_
#define _EX_COMPLIER_H_



/* ==================== [Includes] ========================================== */

#include "ex_common_cfg.h"
#ifdef __cplusplus
extern "C" {
#endif


/* ==================== [Defines] ========================================== */


#if !defined(__FILENAME__)
#if defined(__GNUC__)
/**
 * @brief 获取不含路径的文件名。
 */
#define __FILENAME__ (__builtin_strrchr(__FILE__, '/') \
                        ? (__builtin_strrchr(__FILE__, '/') + 1) \
                        : (__FILE__))
#else
#define __FILENAME__ __FILE__
#endif /* defined(__GNUC__) */
#endif /* !defined(__FILENAME__) */


/* ==================== [Macros] ============================================ */
/**
 * @brief 字符串化。
 *        见：https://gcc.gnu.org/onlinedocs/gcc-3.4.3/cpp/Stringification.html
 */
#ifndef STR
#define STR(x)                          #x
#endif
#ifndef XSTR
#define XSTR(x)                         STR(x)
#endif


/* Compiler Related Definitions */
#if defined(__CC_ARM) || defined(__CLANG_ARM) /* ARM Compiler */

    #include <stdarg.h>
    #define EX_SECTION(x)             __attribute__((section(x)))
    #define EX_USED                   __attribute__((used))
    #define EX_ALIGN(n)               __attribute__((aligned(n)))
    #define EX_WEAK                   __attribute__((weak))
    #define EX_COSTRUCTOR(LEVEL)    __attribute__(constructor(LEVEL))
    #define ex_inline                 static __inline

#elif defined (__IAR_SYSTEMS_ICC__)           /* for IAR Compiler */

    #include <stdarg.h>
    #define EX_SECTION(x)             @ x
    #define EX_USED                   __root
    #define EX_PRAGMA(x)              _Pragma(#x)
    #define EX_ALIGN(n)               EX_PRAGMA(data_alignment=n)
    #define EX_WEAK                   __weak
    #define EX_COSTRUCTOR(LEVEL)      __attribute__(constructor(LEVEL))
    #define ex_inline                 static inline

#elif defined (__GNUC__)                      /* GNU GCC Compiler */

    #include <stdarg.h>
    #define EX_SECTION(x)             __attribute__((section(x)))
    #define EX_USED                   __attribute__((used))
    #define EX_ALIGN(n)               __attribute__((aligned(n)))
    #define EX_WEAK                   __attribute__((weak))
    #define EX_COSTRUCTOR(LEVEL)      __attribute__((constructor(LEVEL)))
    #define ex_inline                 static inline

#else
    #error The current compiler is NOT supported!
#endif



/* ==================== [Typedefs] ========================================== */

/* ==================== [Public Prototypes] ========================================== */

#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EXCOMPLIER_H_
