#ifndef _EX_EXPORT_CONSTRUCTOR_H_
#define _EX_EXPORT_CONSTRUCTOR_H_
/* ==================== [Includes] ========================================== */

#include "../../../exLib/ex_lib.h"
#include "../ex_export_cfg.h"

#ifdef __cplusplus
extern "C" {
#endif


/* ==================== [Defines] ========================================== */
#if EX_EXPROT_METHOD == EX_EXPORT_BY_BFOREMAIN_CONSTRUCTOR
/* ==================== [Macros] ============================================ */
/* public export ------------------------------------------------------------ */
/**
  * @brief  Initialization function exporting macro.
  * @param  _func   The initialization function.
  * @param  _level  The export level, [0, 127].
  * @retval None.
  * @example INIT_EXPORT (bsp_init,EXPORT_LEVEL_BSP) 
  */
#define INIT_EXPORT(_func, _level)                                             \
    void EX_USED EX_COSTRUCTOR((_level)+101)  init_##_func(void)    {\
        EX_LOGD("Export init %s.\r\n", #_func);\
        _func();\
    }
#endif

/* ==================== [Typedefs] ========================================== */

/* ==================== [Global Prototypes] ========================================== */


#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EX_EXPORT_CONSTRUCTOR_H_
