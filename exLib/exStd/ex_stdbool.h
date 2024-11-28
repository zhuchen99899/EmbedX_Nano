/**
 * @file ex_stdbool.h
 * @author ZC (387646983@qq.com)
 * @brief exbool 库
 * @version 0.1
 * @date 2024-11-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _EX_STDBOOL_H_
#define _EX_STDBOOL_H_



/* ==================== [Includes] ========================================== */

#include "ex_std_cfg.h"

#if EX_STDBOOL_IS_ENABLE //当前平台支持标准 stdbool
    #include <stdbool.h>
#endif
#ifdef __cplusplus
extern "C" {
#endif


/* ==================== [Defines] ========================================== */
#if (EX_STDBOOL_IS_ENABLE == 0)//当前平台不支持标准 stdbool
#ifndef bool
#define bool uint8_t   /*!< 布尔类型 */
#define true    1
#define false   0
#endif

#endif

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Global Prototypes] ========================================== */

#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EXSTDBOOL_H_
