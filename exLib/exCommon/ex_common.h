/**
 * @file ex_common.h
 * @author ZC (387646983@qq.com)
 * @brief 通用工具头文件
 * @version 0.1
 * @date 2024-11-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _EX_COMMON_H_
#define _EX_COMMON_H_



/* ==================== [Includes] ========================================== */
#include "ex_common_cfg.h"
#include "ex_macros.h"
#include "ex_err.h"
#include "ex_complier.h"
#include "ex_version.h"
#ifdef __cplusplus
extern "C" {
#endif



/* ==================== [Defines] ========================================== */
#define  ex_systick_t uint64_t
/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */
typedef struct _ex_systime_s{
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
}ex_systime_t;


typedef struct _ex_sysdate_s{
    uint8_t day;
    uint8_t month;
    uint16_t year;
}ex_sysdate_t;
/* ==================== [Public Prototypes] ========================================== */
void ex_systick_inc(void);

ex_systick_t ex_systick_get(void);

uint32_t ex_systime_msec_get();
uint8_t ex_systime_sec_get();
uint8_t ex_systime_min_get();
uint8_t ex_systime_hour_get();


ex_systime_t ex_systime_get(void);

ex_sysdate_t ex_sysdate_get(void);

int32_t ex_task_msec_to_ticks(int32_t msec);
int32_t ex_task_ticks_to_msec(int32_t ticks);
int32_t ex_task_sec_to_ticks(int32_t sec);
int32_t ex_task_ticks_to_sec(int32_t ticks);
#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EXCOMMON_H_
