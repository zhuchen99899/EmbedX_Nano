/**
 * @file ex_err.h
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-11-28
 * @note 错误类型
 * @copyright Copyright (c) 2024
 * 
 */


#ifndef _EX_ERR_H_
#define _EX_ERR_H_


/* ==================== [Includes] ========================================== */

#include "../exStd/ex_stdint.h"

#ifdef __cplusplus
extern "C" {
#endif
/* ==================== [Defines] ========================================== */


/**
 * @brief 错误类型定义。
 *
 * @note  1. 非 0 值都为错误。
 *        2. 建议使用 xf_err_t 作为错误类型，xf_err_code_t 内的值仅用于对比。
 */
typedef enum {
               
                  
    EX_OK                               = 0 ,/*!< 通用成功（执行成功） */
    EX_FAIL                             = -1, /*!< 通用错误（执行失败） */
    EX_ERR_EMPTY                        = -2, /*!< 错误为空 */
    EX_ERR_FULL                         = -3, /*!< 错误已满 */
    EX_ERR_TIMEOUT                      = -4, /*!< 超时 */
    EX_ERR_BUSY                         = -5, /*!< 正忙 */
    EX_ERR_NO_MEMORY                    = -6, /*!< 内存不足 */
    EX_ERR_BUS                          = -7,/*!< 总线忙 */
    EX_ERR_INVALID_ARG                  = -8, /*!< 无效参数 */
    EX_ERR_INVALID_STATE                =-9,/*!< 无效状态 */
    EX_ERR_INVALID_CHECK                =-10,/*!< 无效校验（校验发生错误） */

} ex_err_code_t;



/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/**
 * @brief 整形错误类型。
 * 错误码具体值见 @ref ex_err_code_t.
 * @note 部分编译器需要在选项中选择支持 enum-> int 型
 */
typedef int32_t ex_err_t;

/* ==================== [Public Prototypes] ================================= */

/**
  * @brief 返回 ex_err_code_t 错误代码对应的错误信息字符串
  * @param code ex_err_code_t 错误代码
  * @return 错误信息字符串。
  */
const char *ex_err_to_name(ex_err_t code);
/* ==================== [Public Prototypes] ========================================== */

#ifdef __cplusplus
}
#endif


#endif // _EXERR_H_
