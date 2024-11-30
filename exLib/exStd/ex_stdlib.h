/**
 * @file exStdlib.h
 * @author ZC (387646983@qq.com)
 * @brief exstdlib 库
 * @version 0.1
 * @date 2024-11-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _EX_STDLIB_H_
#define _EX_STDLIB_H_



/* ==================== [Includes] ========================================== */
#include "ex_std_cfg.h"

#if EX_STDLIB_IS_ENABLE  //当前平台支持标准stdlib
#   include <stdlib.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] ========================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Public Prototypes] ========================================== */
//ex平台ex_malloc、ex_free 实现
#define ex_malloc(x)                   ex_user_malloc(x)
#define ex_free(x)                     ex_user_free(x)

#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EXSTDLIB_H_
