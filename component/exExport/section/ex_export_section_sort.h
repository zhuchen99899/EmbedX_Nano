/**
 * @file ex_export_section_sort.h
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-12-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _EX_EXPORT_SECTION_SORT_H_
#define _EX_EXPORT_SECTION_SORT_H_



/* ==================== [Includes] ========================================== */


#include "../../../exLib/ex_lib.h"
#include "../ex_export_cfg.h"

#if !defined(__GNUC__)
#   error "section 需要启用 GNU 特性"
#endif

#if EX_EXPROT_METHOD == EX_EXPORT_BY_SORT_SECTION

#ifdef __cplusplus
extern "C" {
#endif

#define EXPORT_INIT_MAGIC_ID                  (0xa5a5a5a5)

typedef struct ex_export_sort
{
    uint32_t magic_head;
    const char *name;
    void *func;
    int8_t level;
    uint32_t magic_tail;
}ex_export_sort_t;


/* public export ------------------------------------------------------------ */
/**
  * @brief  Initialization function exporting macro.
  * @param  _func   The initialization function.
  * @param  _level  The export level, [0, 127].
  * @retval None.
  * @example INIT_EXPORT (bsp_init,EXPORT_LEVEL_BSP) 
  */
#define INIT_EXPORT(_func, _level)                                             \
    EX_USED const ex_export_sort_t init_##_func EX_SECTION("ex_export") =    \
    {                                                                          \
        .name = XSTR(_func),                                                   \
        .func = (void *)&_func,                                                \
        .level = _level,                                                       \
        .magic_head = EXPORT_INIT_MAGIC_ID,                                         \
        .magic_tail = EXPORT_INIT_MAGIC_ID,                                         \
    }

/* ==================== [Defines] ========================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Public Prototypes] ========================================== */
void ex_export_section_sort_init(void);
#ifdef __cplusplus
}/* extern C */
#endif

#endif//EX_EXPORT_BY_SORT_SECTION 方法

#endif // _EX_EXPORT_SECTION_SORT_H_
