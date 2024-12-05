#include "../../exLib/ex_lib.h"
#include "../../component/exExport/ex_export.h"
EX_TAG("APP");
void app_init(void)
{
   EX_LOGU("app init\r\n");

}

EX_INIT_EXPORT(app_init,EXPORT_LEVEL_APP);

void app2_init(void)
{
   EX_LOGU("app2 init\r\n");

}

EX_INIT_EXPORT(app2_init,EXPORT_LEVEL_APP);