/**
 * @file ex_export_cfg.h
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-12-01
 * @note export组件配置
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _EX_EXPORT_CFG_H_
#define _EX_EXPORT_CFG_H_


#include "../../exLib/ex_lib.h"
/* ==================== [Includes] ========================================== */

#ifdef __cplusplus
extern "C" {
#endif

#define EX_EXPORT_BY_SECTION                    (0) //ATTRIBUTE SECTION 并使用magichead_tail方法，链接器默认soft排序时不需要修改linker脚本
#define EX_EXPORT_BY_CONSTRUCTOR                (1) //ATTRIBUTE CONSTRUCTOR 方法
/* ==================== [Defines] ========================================== */
//默认导出方法
#if !defined(EX_EXPROT_METHOD)
#   define EX_EXPROT_METHOD          EX_EXPORT_BY_SECTION
#endif

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

enum ex_export_level{
    EXPORT_LEVEL_BSP = 0,
    EXPORT_LEVEL_DRIVER = 1,
    EXPORT_LEVEL_MIDWARE = 2,
    EXPORT_LEVEL_DEVICE = 3,
    EXPORT_LEVEL_COMPONENT = 4,
    EXPORT_LEVEL_APP = 5,
    EXPORT_LEVEL_USER = 6
}ex_export_level_t;


typedef struct ex_export
{


    const char *name;
    void *func;
    int8_t level;
    
    #if EX_EXPROT_METHOD==EX_EXPORT_BY_SECTION
    uint32_t magic_head;
    uint32_t magic_tail;
    #endif

}ex_export_t;

// 如果你设置的模式不是这三个，则会报错
#if  EX_EXPROT_METHOD != EX_EXPORT_BY_SECTION && \
    EX_EXPROT_METHOD != EX_EXPORT_BY_CONSTRUCTOR 

#error "EX_EXPROT_METHOD must be EX_EXPORT_BY_SECTION or EX_EXPORT_BY_CONSTRUCTOR!!!"
#endif
/* ==================== [Public Prototypes] ========================================== */

#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EX_EXPORT_CFG_H_
