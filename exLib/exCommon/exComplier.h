#ifndef _EXCOMPLIER_H_
#define _EXCOMPLIER_H_



/* ==================== [Includes] ========================================== */

#include "exCommon_cfg.h"
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
    #define elab_inline                 static __inline

#elif defined (__IAR_SYSTEMS_ICC__)           /* for IAR Compiler */

    #include <stdarg.h>
    #define EX_SECTION(x)             @ x
    #define EX_USED                   __root
    #define EX_PRAGMA(x)              _Pragma(#x)
    #define EX_ALIGN(n)               EX_PRAGMA(data_alignment=n)
    #define EX_WEAK                   __weak
    #define elab_inline                 static inline

#elif defined (__GNUC__)                      /* GNU GCC Compiler */

    #include <stdarg.h>
    #define EX_SECTION(x)             __attribute__((section(x)))
    #define EX_USED                   __attribute__((used))
    #define EX_ALIGN(n)               __attribute__((aligned(n)))
    #define EX_WEAK                   __attribute__((weak))
    #define elab_inline                 static inline

#else
    #error The current compiler is NOT supported!
#endif



/* ==================== [Typedefs] ========================================== */

/* ==================== [Global Prototypes] ========================================== */

#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EXCOMPLIER_H_
