/**
 * @file ex_common.h
 * @author ZC (387646983@qq.com)
 * @brief 通用工具头文件
 * @version 0.1
 * @date 2024-11-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _EX_COMMON_H_
#define _EX_COMMON_H_



/* ==================== [Includes] ========================================== */
#include "ex_common_cfg.h"
#include "ex_macros.h"
#include "ex_err.h"
#include "ex_complier.h"
#include "ex_version.h"
#ifdef __cplusplus
extern "C" {
#endif

void ex_systick_inc(uint32_t tick);

uint32_t ex_systick_get(void);
/* ==================== [Defines] ========================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Public Prototypes] ========================================== */

#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EXCOMMON_H_
