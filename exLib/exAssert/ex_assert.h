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
#ifdef __cplusplus
extern "C" {
#endif


/* ==================== [Defines] ========================================== */



/* ==================== [Typedefs] ========================================== */

/* ==================== [Public Prototypes] ========================================== */

void ex_assert_customize(void);


/* ==================== [Macros] ============================================ */


/**
 * @brief The legacy assert function.
 * @param  condition   The given condition.
 */
#define ex_assert(condition) \
    do{\
        if(!(condition))\
        {\
            EX_LOGE("assert_massage:[%s]",#condition);\
            _assert();\
        }\
    }while(0)

/**
 * @brief  Assert function with ID.
 * @param  condition   The given condition.
 * @param  id_     The given id.
 */
#define ex_assert_id(condition, id_)\
    do{\
        if(!(condition))\
        {\
            EX_LOGE("assert_massage:[%s],the id is [%d]",#condition,id_);\
            _assert();\
        }\
    }while(0)        

/**
 * @brief  Assert function with name.
 * @param  test_   The given condition.
 * @param  name_   The given name.
 */
#define ex_assert_name(condition, name_)\
    do{\
        if(!(condition))\
        {\
            EX_LOGE("assert_name:[%s]",name_);\
            _assert();\
        }\
    }while(0)      

/**
 * @brief  Assert function for checking the given pointer is not NULL.
 * @param  ptr_    The given data pointer.
 */
#define ex_assert_not_null(ptr_)               ex_assert_name((ptr_ != NULL), #ptr_)


void _assert(void);

#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EXASSERT_H_
