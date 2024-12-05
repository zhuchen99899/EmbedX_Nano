#ifndef _EX_EXPORT_REGISTER_H_
#define _EX_EXPORT_REGISTER_H_



/* ==================== [Includes] ========================================== */
#include "../../../exLib/ex_lib.h"
#include "../ex_export_cfg.h"




#ifdef __cplusplus
extern "C" {
#endif

#if     EX_EXPROT_METHOD == EX_EXPORT_BY_CONSTRUCTOR || \
        EX_EXPROT_METHOD == EX_EXPORT_BY_REGISTRY


/* ==================== [Typedefs] ========================================== */


/**
 * @brief 初始化函数链表结构体.
 *
 * @note 基于 registry 初始化时用.
 */
typedef struct _ex_export_registry_node_t {
    ex_list_t node;
    const ex_export_t *const _export;
} _ex_export_registry_node_t;


/* ==================== [Public Prototypes] ========================================== */
/**
 * @brief 注册初始化函数，无需直接调用，使用宏调用
 *
 * @param _node 函数详情结构体
 * @param _level 注册初始化函数的初始化等级
 */
void ex_export_registry_node(_ex_export_registry_node_t *registry_node);

/**
 * @brief 注册函数收集后，统一在此调用初始化函数
 *
 */
void ex_export_from_registry(void);

#endif//EX_EXPROT_METHOD == EX_EXPORT_BY_CONSTRUCTOR EX_EXPORT_BY_REGISTRY   




/* ==================== [Macros] ============================================ */
#if EX_EXPROT_METHOD == EX_EXPORT_BY_REGISTRY

#define INIT_EXPORT(_func, _level)   \
    void  init_##_func(void) { \
        static const ex_export_t CONCAT(__ex_export_, _func) = { \
        .name = XSTR(_func),                                                   \
        .func = (void *)&_func,                                                \
        .level = _level,                                                       \
        };\
        static _ex_export_registry_node_t CONCAT(__ex_init_node_, _func) = { \
            .node       = EX_LIST_HEAD_INIT(CONCAT(__ex_init_node_, _func).node), \
            ._export     = &CONCAT(__ex_export_, _func), \
        };\
        ex_export_registry_node(&CONCAT(__ex_init_node_, _func));\
    \
    };\

#endif//EX_EXPROT_METHOD == EX_EXPORT_BY_REGISTRY



#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EX_EXPORT_REGISTER_H_
