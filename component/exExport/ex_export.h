#ifndef _EX_EXPORT_H_
#define _EX_EXPORT_H_



/* ==================== [Includes] ========================================== */
#include "./section/ex_export_section.h"
#include "./register/ex_export_register.h"
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
