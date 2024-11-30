/**
 * @file ex_assert.c
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-11-28
 * @note exlib 断言功能
 * @copyright Copyright (c) 2024
 * 
 */

#include "ex_assert.h"
#include "../exCommon/ex_complier.h"

/* ==================== [Includes] ========================================== */

/* ==================== [Defines] ========================================== */

ELAB_TAG("exAssert");
/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ========================================== */

/* ==================== [Static Variables] ========================================== */

/* ==================== [Static Functions] ================================== */

/* ==================== [Public Functions] ================================== */

/**
 * @brief customize_assert
 * 
 * @return EX_Weak 
 */
EX_WEAK void ex_assert_customize(void)
{
    //出现断言错误，卡死程序
    while (1)
    {
        /* code */
    }

}

/**
 * @brief customize_assert
 * 
 */
void _assert(void)
{
    EX_LOGD("Assert failure, EmbedX frezz program!!! ");
    ex_assert_customize();

}
