/**
 * @file ex_export_register.c
 * @author ZC (387646983@qq.com)
 * @brief ex_export_register 组件
 * @version 0.1
 * @date 2024-12-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
/* ==================== [Includes] ========================================== */
#include "ex_export_register.h"
/* ==================== [Defines] ========================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ========================================== */

/* ==================== [Static Variables] ========================================== */

/* ==================== [Static Functions] ================================== */

#if     EX_EXPROT_METHOD == EX_EXPORT_BY_CONSTRUCTOR 

EX_TAG("ex_export_register");

static int8_t export_level_max = INT8_MAX;
static ex_list_t ex_export_list_head=EX_LIST_HEAD_INIT(ex_export_list_head);//初始化链表


/* ==================== [Public Functions] ================================== */
/**
 * @brief 注册链表节点，在宏 INIT_EXPORT 中使用
 * 
 * @param registry_node  插入的链表节点
 */
void ex_export_registry_node(ex_export_registry_node_t *registry_node)
{

    //可使用unlikely优化
    if ((NULL == ex_export_list_head.prev)|| (NULL == ex_export_list_head.next)) {
        ex_list_init(&ex_export_list_head);
    }
    if ((NULL ==registry_node->node.prev)
                 || (NULL == registry_node->node.next)) {
        ex_list_init(&registry_node->node);
    }
    // EX_LOGD("add list node %s",registry_node->_export->name);
    ex_list_add(&registry_node->node,&ex_export_list_head);
}


static void ex_export_registry_level_init(int8_t level)
{
    ex_export_registry_node_t *_node = NULL;
    ex_list_for_each_entry(_node,&ex_export_list_head,ex_export_registry_node_t,node){
        if ((_node) && (_node->_export) && (_node->_export->func)) {
            if (_node->_export->level == level)
            {
                ((void (*)(void))_node->_export->func)();
                EX_LOGD("initialize [LEVEL: %d] %s done.", _node->_export->level, 
                                             _node->_export->name);
            }
        }

    }


}


void ex_export_registry_init(void)
{
    for (uint8_t level = 0; level < export_level_max; level ++) //执行所有初始等级的ex_export 段函数
    {
    
    ex_export_registry_level_init(level);
    }
}

#endif //EX_EXPROT_METHOD == EX_EXPORT_BY_CONSTRUCTOR    

