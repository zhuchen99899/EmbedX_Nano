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
static volatile ex_systick_t ex_systick=0;


/* ==================== [Static Functions] ================================== */

static uint32_t tick_increase = TICK_INCREASE_PER_MSEC;





/* ==================== [Public Functions] ================================== */


/**
 * @brief 心跳递增 
 * @note 一般用于中断中增加系统心跳 默认单位 1ms
 * 
 * @param tick 
 */
void ex_systick_inc(void) {
    ex_systick += tick_increase;
}

/**
 * @brief 获取心跳 单位 ms
 * 
 * @return ex_systick_t  
 */
ex_systick_t ex_systick_get(void) {
    return ex_systick;
}


uint32_t ex_systime_msec_get(){

    return (uint32_t)ex_systick;
}
uint8_t ex_systime_sec_get()
{
    return ex_systick/1000;
}

uint8_t ex_systime_min_get()
{
    return ex_systick/1000/60;
}

uint8_t ex_systime_hour_get()
{
    return ex_systick/1000/1000/60;
}

/**
 * @brief 获取系统运行时长
 * 
 * @return ex_systime_t 
 */
ex_systime_t ex_systime_get()
{
ex_systime_t time;
time.seconds=ex_systick/1000;
time.minutes=ex_systick/1000/60;
time.hours=ex_systick/1000/1000/60;
return time;
}

/**
 * @brief 获取系统运行年月日
 * 
 * @return ex_sysdate_t 
 */
ex_sysdate_t ex_sysdate_get()
{
ex_sysdate_t date;
ex_systime_t time=ex_systime_get();
date.day=time.hours/24;
date.month=time.hours/24/30;
date.year=time.hours/24/30/365;
return date;
}


/**
 * @brief 计算1ms 多少tick
 * 
 * @param msec 
 * @return int32_t 
 */
int32_t ex_task_msec_to_ticks(int32_t msec)
{
    int64_t ret = (int64_t)((int64_t)msec);
    if (ret > INT32_MAX || ret < INT32_MIN) {
        return INT32_MAX; // 使用int64_t保证返回类型匹配，但返回一个特殊值表示错误或溢出
    } else if (ret < INT32_MIN) {
        return INT32_MIN;
    } else {
        return ret; // 直接返回计算结果
    }
}

/**
 * @brief 计算1tick 多少ms
 * 
 * @param ticks 
 * @return int32_t 
 */
int32_t ex_task_ticks_to_msec(int32_t ticks)
{
    int64_t ret = (int64_t)(ticks);
    if (ret > INT32_MAX || ret < INT32_MIN) {
        return INT32_MAX; // 使用int64_t保证返回类型匹配，但返回一个特殊值表示错误或溢出
    } else if (ret < INT32_MIN) {
        return INT32_MIN;
    } else {
        return ret; // 直接返回计算结果
    }
}

/**
 * @brief 计算1sec多少ticks
 * 
 * @param sec 
 * @return int32_t 
 */
int32_t ex_task_sec_to_ticks(int32_t sec)
{
    int64_t ret = (int64_t)((int64_t)sec * (int64_t)tick_increase*1000);
    if (ret > INT32_MAX || ret < INT32_MIN) {
        return INT32_MAX; // 使用int64_t保证返回类型匹配，但返回一个特殊值表示错误或溢出
    } else if (ret < INT32_MIN) {
        return INT32_MIN;
    } else {
        return ret; // 直接返回计算结果
    }
}

/**
 * @brief 计算1tick 多少sec
 * 
 * @param ticks 
 * @return int32_t 
 */
int32_t ex_task_ticks_to_sec(int32_t ticks)
{
    int64_t ret = (int64_t)(ticks / (int64_t)(tick_increase*1000));
    if (ret > INT32_MAX || ret < INT32_MIN) {
        return INT32_MAX; // 使用int64_t保证返回类型匹配，但返回一个特殊值表示错误或溢出
    } else if (ret < INT32_MIN) {
        return INT32_MIN;
    } else {
        return ret; // 直接返回计算结果
    }
}