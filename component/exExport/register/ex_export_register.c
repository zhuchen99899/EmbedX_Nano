/* ==================== [Includes] ========================================== */
#include "ex_export_register.h"
/* ==================== [Defines] ========================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ========================================== */

/* ==================== [Static Variables] ========================================== */

/* ==================== [Static Functions] ================================== */

#if     EX_EXPROT_METHOD == EX_EXPORT_BY_CONSTRUCTOR || \
        EX_EXPROT_METHOD == EX_EXPORT_BY_REGISTRY

static uint32_t count_export_init = 0;
static int8_t export_level_max = INT8_MAX;

static ex_list_t ex_export_list_head=EX_LIST_HEAD_INIT(ex_export_list_head);//初始化链表
 
/* ==================== [Public Functions] ================================== */
void ex_export_registry_node(_ex_export_registry_node_t *registry_node)
{

    //可使用unlikely优化
    if ((NULL == ex_export_list_head.prev)|| (NULL == ex_export_list_head.next)) {
        ex_list_init(&ex_export_list_head);
    }
    if (unlikely((NULL ==registry_node->node.prev)
                 || (NULL == registry_node->node.next))) {
        ex_list_init(&registry_node->node);
    }
    ex_list_add(&registry_node->node,&ex_export_list_head);
}


static void ex_export_registry_func_execute(,int8_t level)
{
    /* Execute the poll function in the specific level. */
    for (uint32_t i = 0; i < count_export_init; i ++)
    {
        if (export_init_table[i].level == level)
        {
                EX_LOGD("Export init %s.\r\n", export_init_table[i].name);
                
                ((void (*)(void))export_init_table[i].func)();
        }
    }
}

void ex_export_registry_init(void)
{

    _ex_export_registry_node_t *_node = NULL;
    ex_list_for_each_entry(_node,&ex_export_list_head,_ex_export_registry_node_t,node){
    if
    {
    count_export_init++; //记录总个数
    }



    }


}

#endif //EX_EXPROT_METHOD == EX_EXPORT_BY_CONSTRUCTOR EX_EXPORT_BY_REGISTRY     

