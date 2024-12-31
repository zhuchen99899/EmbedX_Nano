#include "../../exLib/ex_lib.h"
#include "stdlib.h"
EX_TAG("EXLIST_DEMO");
typedef struct export_func{
    const char *name;
    void *func;
    int8_t level;
}export_func_t;

typedef struct ex_node{
    ex_list_t list;
    export_func_t *data;
}ex_node_t;

static ex_list_t list_head=EX_LIST_HEAD_INIT(list_head);


export_func_t *create_export_func(const char *name, void *func, int8_t level) {
    export_func_t *new_func = (export_func_t *)ex_malloc(sizeof(export_func_t));
    new_func->name = name;
    new_func->func = func;
    new_func->level = level;
    return new_func;
}

void insert_node(export_func_t *data) {
    ex_node_t *new_node = (ex_node_t *)ex_malloc(sizeof(ex_node_t));
    new_node->data = data;
    ex_list_init(&new_node->list); // 初始化新节点的链表部分
    ex_list_add(&new_node->list, &list_head); // 将新节点加入链表
}


void print_list(void) {
    ex_node_t *pos=NULL;
    ex_list_for_each_entry(pos, &list_head, ex_node_t, list) {
        
        EX_LOGD("Function Name: %s, Level: %d\n", pos->data->name, pos->data->level);
    }
}




void main()
{
    export_func_t *func1 = create_export_func("func_1", (void *)0x12345678, 6);
    export_func_t *func2 = create_export_func("func_2", (void *)0x87654321, 5);
    export_func_t *func3 = create_export_func("func_3", (void *)0x12342378, 4);
    export_func_t *func4 = create_export_func("func_4", (void *)0x87236432, 3);
    export_func_t *func5 = create_export_func("func_5", (void *)0x12349538, 2);
    export_func_t *func6 = create_export_func("func_6", (void *)0x81236543, 1);
    // 插入节点
    insert_node( func1);
    insert_node(func2);
    insert_node( func3);
    insert_node(func4);
    insert_node( func5);
    insert_node(func6);

    // 打印链表
    print_list();
while (1)
{
    /* code */
}


}