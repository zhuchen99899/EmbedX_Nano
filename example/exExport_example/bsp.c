#include "../../exLib/ex_lib.h"
#include "../../component/exExport/ex_export.h"
EX_TAG("BSP");
void bsp_init(void)
{
   EX_LOGU("BSP init\r\n");
}

EX_INIT_EXPORT(bsp_init,EXPORT_LEVEL_BSP);