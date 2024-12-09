/**
 * @file ex_log.h
 * @author ZC (387646983@qq.com)
 * @brief ex日志工具
 * @version 0.1
 * @date 2024-11-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef EX_LOG_H
#define EX_LOG_H
/* ==================== [Includes] ========================================== */
#include "ex_log_cfg.h"
#include "../exCommon/ex_common.h"
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
              
#define EX_TAG(_tag)  static const char *TAG = _tag

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

/* ==================== [Public Prototypes] ================================= */



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


#   define ex_printf(format,...)      printf(format, ##__VA_ARGS__)

#define LOG_DARK        30
#define LOG_RED         31
#define LOG_GREEN       32
#define LOG_YELLOW      33
#define LOG_BLUE        34
#define LOG_MAGENTA     35
#define LOG_CYAN        36

#define EX_LOG_COLOR_SET(foreColor,backColor) ex_printf("\033[1;%d;%dm", foreColor, (backColor+10))
#define EX_LOG_FORECOLOR_SET(color) ex_printf("\033[1;%dm", color)
#define EX_LOG_COLOR_CLEAR()  ex_printf("\033[0m")


#define EX_LOG_COLOR_SETUP(level, color , format,...) \
    do { \
        EX_LOG_COLOR_CLEAR(); \
        EX_LOG_FORECOLOR_SET(color); \
        ex_log_level(level, TAG, format, ##__VA_ARGS__); \
        EX_LOG_COLOR_CLEAR(); \
    } while (0)


#define EX_LOG_GENERIC(level, color , format,...) \
  do { \
        if (EX_LOG_COLOR_IS_ENABLE) { \
            EX_LOG_COLOR_SETUP(level, color , format, ##__VA_ARGS__); \
        } else { \
            ex_log_level(level, TAG, format, ##__VA_ARGS__); \
        } \
    } while (0)



#if EX_LOG_LEVEL >= EX_LOG_USER
    #define EX_LOGU(format, ...) EX_LOG_GENERIC(EX_LOG_USER, LOG_MAGENTA, format, ##__VA_ARGS__)
#else
    #define EX_LOGU(format, ...) (void)(TAG)
#endif

#if EX_LOG_LEVEL >= EX_LOG_ERROR
    #define EX_LOGE(format, ...) EX_LOG_GENERIC(EX_LOG_ERROR, LOG_RED, format, ##__VA_ARGS__)
#else
    #define EX_LOGE(format, ...) (void)(TAG)
#endif

#if EX_LOG_LEVEL >= EX_LOG_WARN
    #define EX_LOGW(format, ...) EX_LOG_GENERIC(EX_LOG_WARN, LOG_YELLOW, format, ##__VA_ARGS__)
#else
    #define EX_LOGW(format, ...) (void)(TAG)
#endif

#if EX_LOG_LEVEL >= EX_LOG_INFO
    #define EX_LOGI(format, ...) EX_LOG_GENERIC(EX_LOG_INFO, LOG_GREEN, format, ##__VA_ARGS__)
#else
    #define EX_LOGI(format, ...) (void)(TAG)
#endif

#if EX_LOG_LEVEL >= EX_LOG_DEBUG
    #define EX_LOGD(format, ...) EX_LOG_GENERIC(EX_LOG_DEBUG, LOG_BLUE, format, ##__VA_ARGS__)
#else
    #define EX_LOGD(format, ...) (void)(TAG)
#endif

#if EX_LOG_LEVEL >= EX_LOG_VERBOSE
    #define EX_LOGV(format, ...) \
        do { \
            if (EX_LOG_COLOR_IS_ENABLE) { \
                EX_LOG_COLOR_CLEAR(); \
                ex_log_level(EX_LOG_VERBOSE, TAG, format, ##__VA_ARGS__); \
            } else { \
                ex_log_level(EX_LOG_VERBOSE, TAG, format, ##__VA_ARGS__); \
            } \
        } while (0)
#else
    #define EX_LOGV(format, ...) (void)(TAG)
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

