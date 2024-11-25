/**
 * @file exErr.c
 * @author ZC (387646983@qq.com)
 * @brief 错误码转字符
 * @version 0.1
 * @date 2024-11-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
/* ==================== [Includes] ========================================== */
#include "exCommon.h"

/* ==================== [Defines] ========================================== */
/**
 * @brief Error Table Item.
 * 错误码和说明字符串。
 */
#define ERR_TBL_IT(err) {err, XSTR(err)}
/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */
/**
 * @brief 错误码和说明字符串结构体。
 */
typedef struct ex_err_msg_t {
    ex_err_code_t code;
    const char *msg;
} ex_err_msg_t;

/* ==================== [Static Prototypes] ========================================== */

/* ==================== [Static Variables] ========================================== */

#if EX_COMMON_ERR_TO_NAME_LOOKUP_IS_ENABLE
static const ex_err_msg_t ex_err_msg_table[] = {
    
    ERR_TBL_IT(EX_OK),
    ERR_TBL_IT(EX_FAIL),
    ERR_TBL_IT(EX_ERR_EMPTY),
    ERR_TBL_IT(EX_ERR_FULL),
    ERR_TBL_IT(EX_ERR_TIMEOUT),
    ERR_TBL_IT(EX_ERR_BUSY),
    ERR_TBL_IT(EX_ERR_NO_MEMORY),
    ERR_TBL_IT(EX_ERR_BUS),
    ERR_TBL_IT(EX_ERR_INVALID_ARG),
    ERR_TBL_IT(EX_ERR_INVALID_STATE),
    ERR_TBL_IT(EX_ERR_INVALID_CHECK),
};
#endif /* EX_COMMON_ERR_TO_NAME_LOOKUP_IS_ENABLE */

static const char ex_unknown_msg[] = {
#if EX_COMMON_ERR_TO_NAME_LOOKUP_IS_ENABLE
    "ERROR",
#else
    "UNKNOWN ERROR",
#endif
};
/* ==================== [Static Functions] ================================== */

/* ==================== [Global Functions] ================================== */

const char *ex_err_to_name(ex_err_t code)
{
#if EX_COMMON_ERR_TO_NAME_LOOKUP_IS_ENABLE
    unsigned int i = 0;
    for (i = 0; i < (unsigned int)ARRAY_SIZE(ex_err_msg_table); ++i) {
        if (ex_err_msg_table[i].code == code) {
            return ex_err_msg_table[i].msg;
        }
    }
#endif /* EX_COMMON_ERR_TO_NAME_LOOKUP_IS_ENABLE */
    return ex_unknown_msg;
}