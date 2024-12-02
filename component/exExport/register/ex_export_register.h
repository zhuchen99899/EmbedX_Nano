#ifndef _EX_EXPORT_REGISTER_H_
#define _EX_EXPORT_REGISTER_H_



/* ==================== [Includes] ========================================== */
#include "../../../exLib/ex_lib.h"
#include "../ex_export_cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

#if     EX_EXPROT_METHOD == EX_EXPORT_BY_REGISTRY_CONSTRUCTOR || \
        EX_EXPROT_METHOD == EX_EXPORT_BY_REGISTRY


/**
 * @brief 初始化函数类型.
 *
 * @return int
 *      - 0             无异常
 *      - (OTHER)       错误码见 @ref ex_err_code_t.
 */
typedef int (*ex_export_fn_t)(void);





/* ==================== [Typedefs] ========================================== */
/**
 * @brief 初始化函数详情结构体.
 *
 * desc: description.
 *
 *
 */
typedef struct _ex_init_registry_desc_t {
    void *func;                         /*!< 初始化函数 */
    const char *func_name;              /*!< 初始化函数的函数名 */
} ex_init_registry_desc_t;

/**
 * @brief 初始化函数链表结构体.
 *
 * @note 基于 registry 初始化时用.
 */
typedef struct _ex_init_registry_desc_node_t {
    ex_list_t node;
    const ex_init_registry_desc_t *const p_desc;
} ex_init_registry_desc_node_t;


/* ==================== [Public Prototypes] ========================================== */
/**
 * @brief （内部函数）注册初始化函数，无需直接调用，使用宏调用
 *
 * @param p_desc_node 函数详情结构体
 * @param type 注册初始化函数的类型
 */
void ex_export_registry_desc_node(ex_export_registry_desc_node_t *p_desc_node, ex_export_level_t level);

/**
 * @brief 注册函数收集后，统一在此调用初始化函数
 *
 */
void ex_export_from_registry(void);


/* ==================== [Macros] ============================================ */


#endif


#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EX_EXPORT_REGISTER_H_
