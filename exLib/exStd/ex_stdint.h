/**
 * @file exStdint.h
 * @author ZC (387646983@qq.com)
 * @brief exint 库
 * @version 0.1
 * @date 2024-11-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _EX_STDINT_H_
#define _EX_STDINT_H_


/* ==================== [Includes] ========================================== */
#include "ex_std_cfg.h"

#if EX_STDINT_IS_ENABLE //当前平台支持标准stdint
# include <stdint.h>

#if defined(__x86_64__) || defined(__aarch64__)
typedef int64_t                         ex_pointer_t;
#else
typedef int32_t                         ex_pointer_t;

#endif

#endif


#ifdef __cplusplus
extern "C" {
#endif



/* ==================== [Defines] ========================================== */

#if (EX_STDINT_IS_ENABLE == 0) //当前平台不支持标准stdint 
//需要对基本类型做适配

#define int8_t signed   char           /*!<  8bit 整形 */
#define int16_t signed   short         /*!< 16bit 整形 */
#define int32_t signed   int           /*!< 32bit 整形 */
#define uint8_t unsigned char          /*!<  8bit 无符号整形 */
#define uint16_t unsigned short        /*!< 16bit 无符号整形 */
#define uint32_t unsigned int          /*!< 32bit 无符号整形 */
#define intptr_t long     int          /*!< 指针大小类型 */

#ifndef UINT8_MAX
#define UINT8_MAX                       (0xffU)         /*!<  uint8_t 的最大数字 */
#endif
#ifndef UINT16_MAX
#define UINT16_MAX                      (0xffffU)       /*!< uint16_t 的最大数字 */
#endif
#ifndef UINT32_MAX
#define UINT32_MAX                      (0xffffffffU)   /*!< uint32_t 的最大数字 */
#endif

#endif /* (EX_STDINT_IS_ENABLE == 0) */

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Public Prototypes] ========================================== */

#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EXSTDINT_H_
