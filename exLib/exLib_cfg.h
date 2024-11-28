#ifndef _EXLIB_CFG_H_
#define _EXLIB_CFG_H_



/* ==================== [Includes] ========================================== */

#include "./exLog/exLog.h"

#ifdef __cplusplus
extern "C" {
#endif


/* ==================== [Defines] ========================================== */
#define EMBEDX_ENABLED                      (1)
#define EX_STDDEF_ENABLE                    (1)
#define EX_STDINT_ENABLE                    (1)
#define EX_STDBOOL_ENABLE                   (1)
#define EX_STDLIB_ENABLE                    (1)
#define EX_STRING_ENABLE                    (1)


#define EX_COMMON_ERR_TO_NAME_LOOKUP_DISABLE    (0)

#define EX_LOG_DUMP_ENABLE                      (0)


//开启打印等级
#ifdef EX_LOG_LEVEL
#undef EX_LOG_LEVEL
#endif
#   define EX_LOG_LEVEL EX_LOG_VERBOSE 

//开启打印颜色
#   define EX_LOG_COLOR_ENABLE (1)

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Global Prototypes] ========================================== */

#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EXLIB_CFG_H_
