#include "../../exLib/ex_lib.h"
#include "../../component/exExport/ex_export.h"
EX_TAG("MIDWARE");
void midware_init(void)
{
   EX_LOGU("midware init\r\n");

}

EX_INIT_EXPORT(midware_init,EXPORT_LEVEL_MIDWARE);