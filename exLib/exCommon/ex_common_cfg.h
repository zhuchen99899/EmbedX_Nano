/**
 * @file ex_common_cfg.h
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-11-28
 * @note 通用工具配置
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _EX_COMMON_CFG_H_
#define _EX_COMMON_CFG_H_



/* ==================== [Includes] ========================================== */

#include "../ex_lib_cfg.h"

#ifdef __cplusplus
extern "C" {
#endif


/* ==================== [Defines] ========================================== */

/**
 * @brief 是否使能错误码值到字符串的查找表(`EX_OK`->"EX_OK").
 */
#if !defined(EX_COMMON_ERR_TO_NAME_LOOKUP_DISABLE) || (EX_COMMON_ERR_TO_NAME_LOOKUP_DISABLE)
#   define EX_COMMON_ERR_TO_NAME_LOOKUP_IS_ENABLE (0)
#else
#   define EX_COMMON_ERR_TO_NAME_LOOKUP_IS_ENABLE (1)
#endif


/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Public Prototypes] ========================================== */

#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EXCOMMON_CFG_H_
