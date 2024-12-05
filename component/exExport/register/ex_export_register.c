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

#if     EX_EXPROT_METHOD == EX_EXPORT_BY_CONSTRUCTOR || \
        EX_EXPROT_METHOD == EX_EXPORT_BY_REGISTRY

EX_TAG("ex_export_register");

static ex_list_t ex_export_list_head=EX_LIST_HEAD_INIT(ex_export_list_head);//初始化链表


/**
 * @brief 获取链表的节点（假设链表非空）
 *
 * @param list 链表的某个节点中的链表
 * @return ex_export_registry_node_t* 链表节点指针
 */
static ex_export_registry_node_t* ex_export_get_registry_node(ex_list_t *list) {
    return container_of(list->next, ex_export_registry_node_t, node);
}

/**
 * @brief 比较两个节点的 level，
 * 
 * @param node1 第一个节点
 * @param node2 第二个节点
 * @return int 比较结果 <0 : level1 < level2
 * @note 比较函数：根据 _export->level 字段进行排序 level0 在前
 */
static int8_t ex_export_compare(const ex_export_registry_node_t *node1, const ex_export_registry_node_t *node2)
{

 return (node1->_export->level - node2->_export->level);
}

/**
 * @brief 交换两个链表节点的链表
 * 
 * @param list_a 链表1
 * @param list_b 链表2
 */
static void ex_export_swap_nodes(ex_list_t *list_a, ex_list_t *list_b)
{
    if (list_a == list_b) return;
    ex_list_t temp = *list_a;
    *list_a = *list_b;
    *list_b = temp;
}

/**
 * @brief  链表分区：将链表分成两部分
 * 
 * @param left  ：当前需要排序的区间的起始位置
 * @param right ：当前需要排序的区间的结束位置
 * @return ex_list_t*  分区后的中间节点 i
 */
static void ex_export_partition(ex_list_t *left, ex_list_t *right)
{ 
    if (left == right || left->next == right) return ;  // 如果链表分治消失或只有一个节点

    // 选取基准节点 pivot
    ex_export_registry_node_t *pivot = ex_list_entry(left, ex_export_registry_node_t, node); 
    //i标记小于等于基准元素的节点的位置,j用于遍历链表中的节点，找到大于基准元素的节点。
    ex_list_t *i = left->prev,*j = right->next;

    // 分区
    while (j != right) {
        ex_export_registry_node_t *node_j = ex_export_get_registry_node(j);
        if (ex_export_compare(pivot, node_j) > 0) {
            i = i->next;
            ex_export_swap_nodes(i, j);  // 交换节点
        }
        j = j->next;
    }
    // 将基准元素放置到正确的位置
    ex_export_swap_nodes(left, i);
    
    ex_export_partition(left, i);
    ex_export_partition(i->next, right);

}
/**
 * @brief 对整个链表进行快速排序法
 */
void ex_export_quick_sort_all_nodes(void)
{
    if (ex_export_list_head.next == &ex_export_list_head) return;  // 如果链表为空

    ex_export_partition(&ex_export_list_head, ex_export_list_head.prev);
}

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
    ex_list_add(&registry_node->node,&ex_export_list_head);
}


void ex_export_registry_init(void)
{
    ex_export_registry_node_t *_node = NULL;
    ex_export_quick_sort_all_nodes(); //递归快速排序法 //todo 嵌入式栈大小受限，需要改成非递归
    ex_list_for_each_entry(_node,&ex_export_list_head,ex_export_registry_node_t,node){
        if ((_node) && (_node->_export) && (_node->_export->func)) {
                ((void (*)(void))_node->_export->func)();
                EX_LOGD("initialize [LEVEL: %d] %s done.", _node->_export->level, 
                                             _node->_export->name);
            }

    }


}

#endif //EX_EXPROT_METHOD == EX_EXPORT_BY_CONSTRUCTOR EX_EXPORT_BY_REGISTRY     

