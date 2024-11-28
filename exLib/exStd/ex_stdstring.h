/**
 * @file exStdstring.h
 * @author ZC (387646983@qq.com)
 * @brief exStdString库
 * @version 0.1
 * @date 2024-11-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _EX_STDSTRING_H_
#define _EX_STDSTRING_H_



/* ==================== [Includes] ========================================== */

#include "ex_std_cfg.h"

#if EX_STRING_IS_ENABLE //当前平台支持标准stdstring
#   include <string.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


/* ==================== [Defines] ========================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Global Prototypes] ========================================== */

//ex平台ex_memset、ex_bzero、ex_memcpy、ex_memcmp 实现
#define ex_memset(ptr, value, size)    ex_user_memset((void*)(ptr), (value), (size))
#define ex_bzero(ptr, size)            ex_memset((void*)(ptr), 0, (size))
#define ex_memcpy(dest, src, n)        ex_user_memcpy((dest), (src), (n))
#define ex_memcmp(dest, src, n)        ex_user_memcmp((dest), (src), (n))


#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EXSTDSTRING_H_
