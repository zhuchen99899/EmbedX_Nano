#ifndef _XF_NANO_COROUTINE_H_
#define _XF_NANO_COROUTINE_H_



/* ==================== [Includes] ========================================== */


#ifdef __cplusplus
xftern "C" {
#endif



/**
 * @file xf_log.h
 * @author ZC (387646983@qq.com)
 * @brief xf日志工具
 * @version 0.1
 * @date 2024-11-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef XF_LOG_H
#define XF_LOG_H
/* ==================== [Includes] ========================================== */
#include "xf_log_cfg.h"
#include "../xfCommon/xf_common.h"
#ifdef __cplusplus
xftern "C" {
#endif
/* ==================== [Defines] =========================================== */
#define XF_LOG_NONE             (0)
#define XF_LOG_USER             (1)
#define XF_LOG_ERROR            (2)
#define XF_LOG_WARN             (3)
#define XF_LOG_INFO             (4)
#define XF_LOG_DEBUG            (5)
#define XF_LOG_VERBOSE          (6)
              
#define XF_TAG(_tag)  static const char *TAG = _tag

//启用打印到二进制文件
#if XF_LOG_DUMP_IS_ENABLE

#define XF_DUMP_HEAD_BIT        (0) // flags_mask 中表头的标志位
#define XF_DUMP_ASCII_BIT       (1) // flags_mask 中 ASCII 的标志位
#define XF_DUMP_ESCAPE_BIT      (2) // flags_mask 中带有转义字符的标志位
#define XF_DUMP_TAIL_BIT        (3) // flags_mask 中表尾的标志位

#define XF_DUMP_BIT(nr)         BIT(nr)

#define XF_DUMP_TABLE           (XF_DUMP_BIT(XF_DUMP_HEAD_BIT) | XF_DUMP_BIT(XF_DUMP_TAIL_BIT))

/* 只输出 16 进制格式数据 */
#define XF_DUMP_FLAG_HXF_ONLY           (XF_DUMP_TABLE)
/* 输出 16 进制格式数据并带有 ASCII 字符 */
#define XF_DUMP_FLAG_HXF_ASCII          (XF_DUMP_BIT(XF_DUMP_ASCII_BIT) | XF_DUMP_TABLE)
/* 输出 16 进制格式数据、 ASCII 字符、转义字符，其余输出 16 进制原始值 */
#define XF_DUMP_FLAG_HXF_ASCII_ESCAPE   (XF_DUMP_FLAG_HXF_ASCII | XF_DUMP_BIT(XF_DUMP_ESCAPE_BIT))

#endif


/* ==================== [Typedefs] ========================================== */

/* ==================== [Public Prototypes] ================================= */



#if XF_LOG_DUMP_IS_ENABLE
/**
 * @brief 输出内存信息。
 *
 * @param addr 内存地址。
 * @param size 待输出的内存字节长度。
 * @param flags_mask 格式掩码，见 XF_DUMP_FLAG_*。
 * @return xf_err_t
 *      - XF_ERR_INVALID_ARG            参数错误
 *      - XF_OK                         成功
 */
xf_err_t xf_dump_mem(void *addr, size_t size, uint8_t flags_mask);
#endif

/* ==================== [Macros] ============================================ */

// exlog对接:如果不独立对接ex_log_level，则会调用ex_log_printf实现
#if !defined(ex_log_level) && defined(ex_log_printf)
    #if (EX_TICK_ENABLE ==1)
    #define ex_log_level(level, tag, format, ...) ex_log_printf("%c-[<%s>(%s):%d](t:%d): "format"\n", #level[7], tag,__FUNCTION__, __LINE__,ex_systick_get(),##__VA_ARGS__)
    #else 
    #define ex_log_level(level, tag, format, ...) ex_log_printf("%c-[<%s>(%s):%d]: "format"\n", #level[7], tag,__FUNCTION__, __LINE__,##__VA_ARGS__)
    #endif
#endif

#   define xf_printf(format,...)      printf(format, ##__VA_ARGS__)

#define LOG_DARK        30
#define LOG_RED         31
#define LOG_GREEN       32
#define LOG_YELLOW      33
#define LOG_BLUE        34
#define LOG_MAGENTA     35
#define LOG_CYAN        36

#define XF_LOG_COLOR_SET(foreColor,backColor) xf_printf("\033[1;%d;%dm", foreColor, (backColor+10))
#define XF_LOG_FORECOLOR_SET(color) xf_printf("\033[1;%dm", color)
#define XF_LOG_COLOR_CLEAR()  xf_printf("\033[0m")


#define XF_LOG_COLOR_SETUP(level, color , format,...) \
    do { \
        XF_LOG_COLOR_CLEAR(); \
        XF_LOG_FORECOLOR_SET(color); \
        xf_log_level(level, TAG, format, ##__VA_ARGS__); \
        XF_LOG_COLOR_CLEAR(); \
    } while (0)


#define XF_LOG_GENERIC(level, color , format,...) \
  do { \
        if (XF_LOG_COLOR_IS_ENABLE) { \
            XF_LOG_COLOR_SETUP(level, color , format, ##__VA_ARGS__); \
        } else { \
            xf_log_level(level, TAG, format, ##__VA_ARGS__); \
        } \
    } while (0)



#if XF_LOG_LEVEL >= XF_LOG_USER
    #define XF_LOGU(format, ...) XF_LOG_GENERIC(XF_LOG_USER, LOG_MAGENTA, format, ##__VA_ARGS__)
#else
    #define XF_LOGU(format, ...) (void)(TAG)
#endif

#if XF_LOG_LEVEL >= XF_LOG_ERROR
    #define XF_LOGE(format, ...) XF_LOG_GENERIC(XF_LOG_ERROR, LOG_RED, format, ##__VA_ARGS__)
#else
    #define XF_LOGE(format, ...) (void)(TAG)
#endif

#if XF_LOG_LEVEL >= XF_LOG_WARN
    #define XF_LOGW(format, ...) XF_LOG_GENERIC(XF_LOG_WARN, LOG_YELLOW, format, ##__VA_ARGS__)
#else
    #define XF_LOGW(format, ...) (void)(TAG)
#endif

#if XF_LOG_LEVEL >= XF_LOG_INFO
    #define XF_LOGI(format, ...) XF_LOG_GENERIC(XF_LOG_INFO, LOG_GREEN, format, ##__VA_ARGS__)
#else
    #define XF_LOGI(format, ...) (void)(TAG)
#endif

#if XF_LOG_LEVEL >= XF_LOG_DEBUG
    #define XF_LOGD(format, ...) XF_LOG_GENERIC(XF_LOG_DEBUG, LOG_BLUE, format, ##__VA_ARGS__)
#else
    #define XF_LOGD(format, ...) (void)(TAG)
#endif

#if XF_LOG_LEVEL >= XF_LOG_VERBOSE
    #define XF_LOGV(format, ...) \
        do { \
            if (XF_LOG_COLOR_IS_ENABLE) { \
                XF_LOG_COLOR_CLEAR(); \
                xf_log_level(XF_LOG_VERBOSE, TAG, format, ##__VA_ARGS__); \
            } else { \
                xf_log_level(XF_LOG_VERBOSE, TAG, format, ##__VA_ARGS__); \
            } \
        } while (0)
#else
    #define XF_LOGV(format, ...) (void)(TAG)
#endif


#if XF_LOG_DUMP_IS_ENABLE

#define XF_LOG_BUFFER_HXF(buffer, buffer_len)     xf_dump_mem(buffer, buffer_len, XF_DUMP_FLAG_HXF_ONLY)
#define XF_LOG_BUFFER_HXFDUMP(buffer, buffer_len)    xf_dump_mem(buffer, buffer_len, XF_DUMP_FLAG_HXF_ASCII)
#define XF_LOG_BUFFER_HXFDUMP_ESCAPE(buffer, buffer_len) xf_dump_mem(buffer, buffer_len, XF_DUMP_FLAG_HXF_ASCII_ESCAPE)

#else

#define XF_LOG_BUFFER_HXF(buffer, buffer_len)
#define XF_LOG_BUFFER_HXFDUMP(buffer, buffer_len)
#define XF_LOG_BUFFER_HXFDUMP_ESCAPE(buffer, buffer_len)

#endif // XF_LOG_DUMP_IS_ENABLE
#ifdef __cplusplus
} /* xftern "C" */
#endif

#endif




/* ==================== [Defines] ========================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Public Prototypes] ========================================== */

#ifdef __cplusplus
}/* xftern C */
#endif


#endif // _XF_NANO_COROUTINE_H_
