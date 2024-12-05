#include "../../exLib/ex_lib.h"
#include "../../component/exExport/ex_export.h"
EX_TAG("COMPONENT");
void component_init(void)
{
   EX_LOGU("component init\r\n");

}

EX_INIT_EXPORT(component_init,EXPORT_LEVEL_COMPONENT);