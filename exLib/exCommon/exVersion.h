#ifndef _EXVERSION_H_
#define _EXVERSION_H_



/* ==================== [Includes] ========================================== */
#include "exComplier.h"

#ifdef __cplusplus
extern "C" {
#endif


/* ==================== [Defines] ========================================== */
/* 主要版本号 (X.x.x) */
#define EX_VERSION_MAJOR   0
/* 次要版本号 (x.X.x) */
#define EX_VERSION_MINOR   1
/* 补丁版本号 (x.x.X) */
#define EX_VERSION_PATCH   0
/* ==================== [Macros] ============================================ */

/**
 * @brief 将版本号转换为整数的宏。
 */

#define EX_VERSION_VAL(major, minor, patch) \
    (((major) << 16) | ((minor) << 8) | (patch))

/**
 * @brief 当前版本号, 返回一个整数。
 * 编译时使用。比如：EX_VERSION >= EX_VERSION_VAL(1, 0, 0)
 */
#define EX_VERSION \
    EX_VERSION_VAL(EX_VERSION_MAJOR, EX_VERSION_MINOR, EX_VERSION_PATCH)

/**
 * @brief 当前版本号, 返回一个字符串。
 */
#define EX_VERSION_STR \
    "v" XSTR(EX_VERSION_MAJOR) "." XSTR(EX_VERSION_MINOR) "." XSTR(EX_VERSION_PATCH)

/* ==================== [Typedefs] ========================================== */

/* ==================== [Global Prototypes] ========================================== */

#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EXVERSION_H_
