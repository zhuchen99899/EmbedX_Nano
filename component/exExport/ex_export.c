/**
 * @file ex_export.c
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-12-01
 * @note export初始化组件
 * @copyright Copyright (c) 2024
 * 
 */

#include "ex_export.h"

/* ==================== [Includes] ========================================== */

/* ==================== [Defines] ========================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ========================================== */

/* ==================== [Static Variables] ========================================== */

/* ==================== [Static Functions] ================================== */

/* ==================== [Public Functions] ================================== */

ex_err_t ex_export_init(void)
{
    ex_err_t ret;
    #if(EX_EXPROT_METHOD==EX_EXPORT_BY_SECTION)
        ex_export_section_init();
    #elif (EX_EXPROT_METHOD==EX_EXPORT_BY_CONSTRUCTOR)
        ex_export_registry_init();
    #endif


    ret=EX_OK;
    return ret;
}