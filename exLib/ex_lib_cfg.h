/**
 * @file ex_lib_cfg.h
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-11-29
 * @note exlib 配置
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _EX_LIB_CFG_H_
#define _EX_LIB_CFG_H_



/* ==================== [Includes] ========================================== */

#include "./exLog/ex_log.h"

#ifdef __cplusplus
extern "C" {
#endif


/* ==================== [Defines] ========================================== */
//标准库支持
#define EMBEDX_ENABLED                      (1)
#define EX_STDDEF_ENABLE                    (1)
#define EX_STDINT_ENABLE                    (1)
#define EX_STDBOOL_ENABLE                   (1)
#define EX_STDLIB_ENABLE                    (1)
#define EX_STRING_ENABLE                    (1)


//是否使能错误码值到字符串的查找表
#define EX_COMMON_ERR_TO_NAME_LOOKUP_DISABLE    (1)


//是否使能打印到二进制文件
#define EX_LOG_DUMP_ENABLE                   (0)


//设置打印等级
#ifdef EX_LOG_LEVEL
#undef EX_LOG_LEVEL
#endif
#   define EX_LOG_LEVEL EX_LOG_VERBOSE 

//支持打印颜色
#   define EX_LOG_COLOR_ENABLE (1)

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Global Prototypes] ========================================== */

#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EXLIB_CFG_H_
