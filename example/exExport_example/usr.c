#include "../../exLib/ex_lib.h"
#include "../../component/exExport/ex_export.h"
EX_TAG("usr");
void usr_init(void)
{
   EX_LOGU("usr init\r\n");

}

EX_INIT_EXPORT(usr_init,EXPORT_LEVEL_USER);