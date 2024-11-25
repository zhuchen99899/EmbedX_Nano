/**
 * @file exLog_cfg.h
 * @author ZC (387646983@qq.com)
 * @brief ex日志工具配设接口
 * @version 0.1
 * @date 2024-11-25
 * @note 启用EMBEDX平台默认支持exLog
 * @note exLog 优先使用自己定义的ex_log_printf，如果没有定义，则默认使用printf。打印二进制同理，默认后端为printf
 * @note 默认输出等级 EX_LOG_INFO
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _EXLOG_CFG_H_
#define _EXLOG_CFG_H_
/* ==================== [Includes] ========================================== */
#include "../exLib_cfg.h"
/*启动embedx 框架后默认使用exlog功能 */
#if defined(EMBEDX_ENABLED)
#define EMBEDX_IS_ENABLED (1)
#else
#define EMBEDX_IS_ENABLED (0)
#endif

#if EMBEDX_IS_ENABLED 
#include <stdio.h>
#endif

#if EX_LOG_DUMP_ENABLE
#   define EX_LOG_DUMP_IS_ENABLE (1)
#else
#   define EX_LOG_DUMP_IS_ENABLE (0)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== [Defines] =========================================== */
// 默认输出等级
#ifndef EX_LOG_LEVEL
#   define EX_LOG_LEVEL EX_LOG_INFO 
#endif


#if (EX_LOG_LEVEL < 0) || (EX_LOG_LEVEL > 6)
#   error "log level must between 0 to 6"
#endif

// ex_log_printf 默认对接printf，嵌入式平台需要实现printf支持
#if !defined(ex_log_printf)
#   define ex_log_printf(format, ...) printf(format, ##__VA_ARGS__)
#endif


// exlog 打印二进制的后端，默认使用ex_log_printf打印
#if !defined(ex_log_dump_printf)
#   define ex_log_dump_printf(format, ...) ex_log_printf(format, ##__VA_ARGS__)
#endif


// exlog对接:如果不独立对接ex_log_level，则会调用ex_log_printf实现
#if !defined(ex_log_level) && defined(ex_log_printf)
#define ex_log_level(level, tag, format, ...) ex_log_printf("%c-%s[:%d(%s)]: "format"\n", #level[7], tag, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // _EXLOG_CFG_H_

