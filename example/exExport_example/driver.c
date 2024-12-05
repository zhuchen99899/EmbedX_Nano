#include "../../exLib/ex_lib.h"
#include "../../component/exExport/ex_export.h"
EX_TAG("DRIVER");
void driver_init(void)
{
   EX_LOGU("driver init\r\n");

}

EX_INIT_EXPORT(driver_init,EXPORT_LEVEL_DRIVER);