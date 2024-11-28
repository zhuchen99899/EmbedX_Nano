/**
 * @file ex_std_cfg.h
 * @author ZC (387646983@qq.com)
 * @brief  ex标准库接口
 * @version 0.1
 * @date 2024-11-25
 * @note 标准库配设
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _EX_STD_CFG_H_
#define _EX_STD_CFG_H_



/* ==================== [Includes] ========================================== */
#include "../ex_lib_cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] ========================================== */


#if EX_STDDEF_ENABLE
#   define EX_STDDEF_IS_ENABLE     (1)
#else
#   define EX_STDDEF_IS_ENABLE     (0)
#endif

#if EX_STDINT_ENABLE
#   define EX_STDINT_IS_ENABLE     (1)
#else
#   define EX_STDDEF_IS_ENABLE     (0)
#endif

#if  EX_STDBOOL_ENABLE
#   define EX_STDBOOL_IS_ENABLE     (1)
#else
#   define EX_STDBOOL_IS_ENABLE     (0)
#endif



/**
 * @defgroup  ex_stdlib 配置.
 * @{
 */

#if EX_STDLIB_ENABLE
#   define EX_STDLIB_IS_ENABLE     (1)
#else
#   define EX_STDLIB_IS_ENABLE     (0)
#endif


#ifndef ex_user_malloc
#   define ex_user_malloc(x) malloc(x)
#endif

#ifndef ex_user_free
#   define ex_user_free(x) free(x)
#endif


/**
 * @defgroup  ex_string 配置.
 * @{
 */

#if EX_STRING_ENABLE
#   define EX_STRING_IS_ENABLE     (1)
#else
#   define EX_STRING_IS_ENABLE     (0)
#endif

#ifndef ex_user_memcpy
#   define ex_user_memcpy(dest, src, n)   memcpy(dest, src, n)
#endif

#ifndef ex_user_memcmp
#   define ex_user_memcmp(dest, src, n)   memcmp(dest, src, n)
#endif

#ifndef ex_user_memset
#   define ex_user_memset(ptr, value, size) memset((ptr), (value), (size))
#endif


/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Global Prototypes] ========================================== */

#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EXSTD_CFG_H_
