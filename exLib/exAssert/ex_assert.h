/**
 * @file ex_assert.h
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-11-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _EX_ASSERT_H_
#define _EX_ASSERT_H_



/* ==================== [Includes] ========================================== */
#include "../exCommon/ex_common.h"
#include "../exLog/ex_log.h"
#include 
#ifdef __cplusplus
extern "C" {
#endif


/* ==================== [Defines] ========================================== */



/* ==================== [Typedefs] ========================================== */

/* ==================== [Global Prototypes] ========================================== */

//todo 完成自定义assert (_weak 定义或回调)




/* ==================== [Macros] ============================================ */

//todo 完成assert
#ifndef assert
#define assert(str,id,tag) EX_LOGE("Assert failure!: %s.\r\n", #str);
#endif // !1

#define ex_assert(condition) \
    do{\
        if(!(condition))\
        {\
            
        }\
    }while(0);
#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EXASSERT_H_
