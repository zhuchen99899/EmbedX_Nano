#include "../../exLib/ex_lib.h"
#include "../../component/exExport/ex_export.h"
EX_TAG("DEVICE");
void device_init(void)
{
   EX_LOGU("device init\r\n");

}

EX_INIT_EXPORT(device_init,EXPORT_LEVEL_DEVICE);