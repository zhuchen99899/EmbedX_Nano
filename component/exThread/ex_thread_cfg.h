/**
 * @file ex_thread_cfg.h
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-12-24
 * @note nano裸机版本任务调度器 配设文件
 * @copyright Copyright (c) 2024
 * 
 * 
 */

#ifndef _EX_THREAD_CFG_H_
#define _EX_THREAD_CFG_H_

/**
 * @brief 配置任务最高优先级
 */
#ifndef EX_TASK_PRIORITY_LEVELS
#   define EX_TASK_PRIORITY_LEVELS  255
#endif

typedef enum _ex_task_type_s{
   _EX_TASK_TYPE_TIMER = 0,
   _EX_TASK_TYPE_MAX 
}ex_task_type_t; //任务类型


/* ==================== [Includes] ========================================== */


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


#endif // _EX_THREAD_CFG_H_
