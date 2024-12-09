/**
 * @file ex_time.c
 * @author ZC (387646983@qq.com)
 * @brief 获取时钟计数
 * @version 0.1
 * @date 2024-12-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */
/* ==================== [Includes] ========================================== */
#include "ex_common.h"
/* ==================== [Defines] ========================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ========================================== */

/* ==================== [Static Variables] ========================================== */
static uint32_t ex_systick;

/* ==================== [Static Functions] ================================== */
void ex_systick_inc(uint32_t tick) {
    ex_systick += tick;
}

uint32_t ex_systick_get(void) {
    return ex_systick;
}

/* ==================== [Public Functions] ================================== */

