/**
 * @file ex_thread.h
 * @author ZC (387646983@qq.com)
 * @brief exThread库
 * @version 0.1
 * @date 2024-12-08
 * @note nano裸机版本任务调度器 
 * @copyright Copyright (c) 2024
 * @note //TODO : 1.实现定时调度 2.实现消息队列 3.实现消息队列 4.实现消息订阅发布总线
 * 
 */
#ifndef _EX_THREAD_H_
#define _EX_THREAD_H_



/* ==================== [Includes] ========================================== */
#include "cmsis_os2.h"
#include "exNanoTask/ex_nano_scheduler.h"
#include "exNanoTimer/ex_nano_timer.h"
#include "exNanoTask/ex_nano_kernel.h"
#ifdef __cplusplus
extern "C" {
#endif


/* ==================== [Defines] ========================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Public Prototypes] ========================================== */

#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EX_THREAD_H_
