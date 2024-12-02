#include "../../exLib/ex_lib.h"
#include "../../component/exExport/ex_export.h"
EX_TAG("BSP");
void bsp_init(void)
{
   EX_LOGU("BSP init\r\n");
   XF_INIT_EXPORT_REGISTRY(bsp_init,EXPORT_LEVEL_BSP);
}

//EX_INIT_EXPORT(bsp_init,EXPORT_LEVEL_BSP);

void test_driver_init(void)
{
   EX_LOGU("test_drivet_init\r\n");
   XF_INIT_EXPORT_REGISTRY(bsp_init,EXPORT_LEVEL_BSP);

}

//EX_INIT_EXPORT(test_driver_init,EXPORT_LEVEL_DRIVER);