#ifndef _EX_EXPORT_H_
#define _EX_EXPORT_H_



/* ==================== [Includes] ========================================== */
#include "ex_export_section_sort.h"

#ifdef __cplusplus
extern "C" {
#endif


/* ==================== [Defines] ========================================== */
#define EX_INIT_EXPORT(_func, _level)  INIT_EXPORT(_func, _level)
/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Public Prototypes] ========================================== */
ex_err_t ex_export_init(void);
#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EX_EXPORT_H_
