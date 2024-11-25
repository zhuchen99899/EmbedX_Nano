/**
 * @file exLog.h
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-11-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef EXLOG_H
#define EXLOG_H
/* ==================== [Includes] ========================================== */
#include "exLog_cfg.h"

#ifdef __cplusplus
extern "C" {
#endif
/* ==================== [Defines] =========================================== */
#define EX_LOG_NONE             (0)
#define EX_LOG_USER             (1)
#define EX_LOG_ERROR            (2)
#define EX_LOG_WARN             (3)
#define EX_LOG_INFO             (4)
#define EX_LOG_DEBUG            (5)
#define EX_LOG_VERBOSE          (6)

//启用打印到二进制文件
#if EX_LOG_DUMP_IS_ENABLE

#define EX_DUMP_HEAD_BIT        (0) // flags_mask 中表头的标志位
#define EX_DUMP_ASCII_BIT       (1) // flags_mask 中 ASCII 的标志位
#define EX_DUMP_ESCAPE_BIT      (2) // flags_mask 中带有转义字符的标志位
#define EX_DUMP_TAIL_BIT        (3) // flags_mask 中表尾的标志位

#define EX_DUMP_BIT(nr)         BIT(nr)

#define EX_DUMP_TABLE           (EX_DUMP_BIT(EX_DUMP_HEAD_BIT) | EX_DUMP_BIT(EX_DUMP_TAIL_BIT))

/* 只输出 16 进制格式数据 */
#define EX_DUMP_FLAG_HEX_ONLY           (EX_DUMP_TABLE)
/* 输出 16 进制格式数据并带有 ASCII 字符 */
#define EX_DUMP_FLAG_HEX_ASCII          (EX_DUMP_BIT(EX_DUMP_ASCII_BIT) | EX_DUMP_TABLE)
/* 输出 16 进制格式数据、 ASCII 字符、转义字符，其余输出 16 进制原始值 */
#define EX_DUMP_FLAG_HEX_ASCII_ESCAPE   (EX_DUMP_FLAG_HEX_ASCII | EX_DUMP_BIT(EX_DUMP_ESCAPE_BIT))

#endif
/* ==================== [Typedefs] ========================================== */

/* ==================== [Global Prototypes] ================================= */



#if EX_LOG_DUMP_IS_ENABLE
/**
 * @brief 输出内存信息。
 *
 * @param addr 内存地址。
 * @param size 待输出的内存字节长度。
 * @param flags_mask 格式掩码，见 EX_DUMP_FLAG_*。
 * @return ex_err_t
 *      - EX_ERR_INVALID_ARG            参数错误
 *      - EX_OK                         成功
 */
ex_err_t ex_dump_mem(void *addr, size_t size, uint8_t flags_mask);
#endif

/* ==================== [Macros] ============================================ */

#if EX_LOG_LEVEL >= EX_LOG_USER
#   define EX_LOGU(tag, format, ...)  ex_log_level(EX_LOG_USER,     tag, format, ##__VA_ARGS__)
#else
#   define EX_LOGU(tag, format, ...)  (void)(tag)
#endif

#if EX_LOG_LEVEL >= EX_LOG_ERROR
#   define EX_LOGE(tag, format, ...)  ex_log_level(EX_LOG_ERROR,    tag, format, ##__VA_ARGS__)
#else
#   define EX_LOGE(tag, format, ...)  (void)(tag)
#endif

#if EX_LOG_LEVEL >= EX_LOG_WARN
#   define EX_LOGW(tag, format, ...)  ex_log_level(EX_LOG_WARN,     tag, format, ##__VA_ARGS__)
#else
#   define EX_LOGW(tag, format, ...)  (void)(tag)
#endif

#if EX_LOG_LEVEL >= EX_LOG_INFO
#   define EX_LOGI(tag, format, ...)  ex_log_level(EX_LOG_INFO,     tag, format, ##__VA_ARGS__)
#else
#   define EX_LOGI(tag, format, ...)  (void)(tag)
#endif

#if EX_LOG_LEVEL >= EX_LOG_DEBUG
#   define EX_LOGD(tag, format, ...)  ex_log_level(EX_LOG_DEBUG,    tag, format, ##__VA_ARGS__)
#else
#   define EX_LOGD(tag, format, ...)  (void)(tag)
#endif

#if EX_LOG_LEVEL >= EX_LOG_VERBOSE
#   define EX_LOGV(tag, format, ...)  ex_log_level(EX_LOG_VERBOSE,  tag, format, ##__VA_ARGS__)
#else
#   define EX_LOGV(tag, format, ...)  (void)(tag)
#endif

#if EX_LOG_DUMP_IS_ENABLE

#define EX_LOG_BUFFER_HEX(buffer, buffer_len)     ex_dump_mem(buffer, buffer_len, EX_DUMP_FLAG_HEX_ONLY)
#define EX_LOG_BUFFER_HEXDUMP(buffer, buffer_len)    ex_dump_mem(buffer, buffer_len, EX_DUMP_FLAG_HEX_ASCII)
#define EX_LOG_BUFFER_HEXDUMP_ESCAPE(buffer, buffer_len) ex_dump_mem(buffer, buffer_len, EX_DUMP_FLAG_HEX_ASCII_ESCAPE)

#else

#define EX_LOG_BUFFER_HEX(buffer, buffer_len)
#define EX_LOG_BUFFER_HEXDUMP(buffer, buffer_len)
#define EX_LOG_BUFFER_HEXDUMP_ESCAPE(buffer, buffer_len)

#endif // EX_LOG_DUMP_IS_ENABLE
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

