/**
 * @file exList.h
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-11-28
 * @note code from linux kernel
 * @copyright Copyright (c) 2024
 * 
 */


#ifndef _EXLIST_H_
#define _EXLIST_H_



/* ==================== [Includes] ========================================== */
#include "../exCommon/exMacros.h" //offsetof and container_of support for list

#ifdef __cplusplus
extern "C" {
#endif


/* ==================== [Defines] ========================================== */

//野指针地址
#if !defined(EX_LIST_POISON1)
#   define EX_LIST_POISON1              0x002431f2
#endif
#if !defined(EX_LIST_POISON2)
#   define EX_LIST_POISON2              0x0032f22a
#endif

/* ==================== [Typedefs] ========================================== */

/**
 * @brief 双向链表
 * 
 */
struct ex_list_head{
    struct ex_list_head *next, *prev;
};
typedef struct ex_list_head ex_list_t;

/*
 * Simple doubly linked list implementation.
 *
 * Some of the internal functions ("__xxx") are useful when
 * manipulating whole lists rather than single entries, as
 * sometimes we already know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 */
//static define
/**
 * @brief 在静态定义时初始化链表
 *
 * @example: exlist_head_t = EX_LIST_HEAD_INIT(list);
 */
#define EX_LIST_HEAD_INIT(name) { &(name), &(name) }

/**
 * @brief 定义一个名叫 `name` 的链表, 且以 `name` 为链表头.
 */
#define EX_LIST_HEAD(name) \
    struct list_head name = EX_LIST_HEAD_INIT(name)


/* ==================== [Global Prototypes] ========================================== */

//dynamtic create
/**
 * @brief 动态初始化链表.
 *
 * @param list 被初始化的链表节点.
 */
static inline void ex_list_init(ex_list_t *list)
{
    list->next = list;
    list->prev = list;
}

/*
 * Insert a new_node entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */

/**
 * @brief 在两个已知的连续节点之间插入一个 new_node 节点.
 *
 * @attention 仅用于内部链表操作, 因为已经知道前一个/后一个节点！
 *
 * @param new_node
 * @param prev
 * @param next
 */
static inline void __ex_list_add(ex_list_t *new_node, ex_list_t *prev, ex_list_t *next)
{
    next->prev      = new_node;
    new_node->next  = next;
    new_node->prev  = prev;
    prev->next      = new_node;
}

/**
 * list_add - add a new_node entry
 * @new_node: new_node entry to be added
 * @head: list head to add it after
 *
 * Insert a new_node entry after the specified head.
 * This is good for implementing stacks.
 */

/**
 * @brief ex_list_add - 在指定节点之后添加一个 new_node.
 *
 * 这对于实现栈(stacks)很有好处.
 *
 * @param new_node 要添加的 new_node.
 * @param head 需要添加 new_node 到其后面的节点,
 * 也就是 new_node 将添加到 head 节点后面.
 */
static inline void ex_list_add(ex_list_t *new_node, ex_list_t *head)
{
    __ex_list_add(new_node, head, head->next);
}



/**
 * list_add_tail - add a new_node entry
 * @new_node: new_node entry to be added
 * @head: list head to add it before
 *
 * Insert a new_node entry before the specified head.
 * This is useful for implementing queues.
 */

/**
 * @brief ex_list_add_tail - 在指定节点之前添加一个 new_node.
 *
 * 这对于实现队列(queues)很有用.
 *
 * @param new_node 要添加的 new_node.
 * @param head 需要添加 new_node 到其前面的节点,
 * 也就是 new_node 将添加到 head 节点前面.
 */
static inline void ex_list_add_tail(ex_list_t *new_node, ex_list_t *head)
{
    __ex_list_add(new_node, head->prev, head);
}


/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty() on entry does not return true after this, the entry is
 * in an undefined state.
 */

/**
 * @brief 删除链表节点(list entry), 使前一个/后一个节点相互指向.
 *
 * @attention 仅用于内部链表操作, 因为已经知道前一个/后一个节点！
 *
 * @param prev
 * @param next
 */
static inline void __ex_list_del(ex_list_t *prev, ex_list_t *next)
{
    next->prev = prev;
    prev->next = next;
}


/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty() on entry does not return true after this, the entry is
 * in an undefined state.
 */

static inline void __ex_list_del_entry(ex_list_t *entry)
{
    __ex_list_del(entry->prev, entry->next);
}

/**
 * @brief ex_list_del - 从链表中删除节点.
 *
 * @param entry 要从链表中删除的元素.
 *
 * @note 之后, 节点上的 ex_list_empty() 不会返回 true, 此时节点处于未定义状态.
 */
static inline void ex_list_del(ex_list_t *entry)
{
    __ex_list_del(entry->prev, entry->next);
    entry->next = (ex_list_t *)EX_LIST_POISON1;
    entry->prev = (ex_list_t *)EX_LIST_POISON2;
}

/**
 * list_replace - replace old entry by new_node one
 * @old : the element to be replaced
 * @new_node : the new_node element to insert
 *
 * If @old was empty, it will be overwritten.
 */

/**
 * @brief ex_list_replace - 用 new_node 替换旧节点.
 *
 * 如果 @old 为空, 则会被覆盖. (If @old was empty, it will be overwritten.)
 *
 * @param old 被替换的节点.
 * @param new_node 要插入的 new_node 节点.
 */
static inline void ex_list_replace(ex_list_t *old, ex_list_t *new_node)
{
    new_node->next          = old->next;
    new_node->next->prev    = new_node;
    new_node->prev          = old->prev;
    new_node->prev->next    = new_node;
}

/**
 * @brief ex_list_replace_init - 用 new_node 替换旧节点, 并重新初始化旧节点.
 *
 * @param old 被替换的节点.
 * @param new_node 要插入的 new_node 节点.
 */
static inline void ex_list_replace_init(ex_list_t *old, ex_list_t *new_node)
{
    ex_list_replace(old, new_node);
    ex_list_init(old);
}

/**
 * list_del_init - deletes entry from list and reinitialize it.
 * @entry: the element to delete from the list.
 */

/**
 * @brief ex_list_del_init - 从链表中删除节点, 并重新初始化.
 *
 * @param entry 要从链表中删除的节点.
 */
static inline void ex_list_del_init(ex_list_t *entry)
{
    __ex_list_del_entry(entry);
    ex_list_init(entry);
}

/**
 * list_move - delete from one list and add as another's head
 * @list: the entry to move
 * @head: the head that will precede our entry
 */

/**
 * @brief ex_list_move - 从一个链表中删除指定节点, 并添加为另一个链表的头节点.
 *
 * @param list 要移动的节点.
 * @param head list 节点进入之前的头节点,
 *  也就是 list 进入之后, head 变为 list 后一个节点.
 */
static inline void ex_list_move(ex_list_t *list, ex_list_t *head)
{
    __ex_list_del_entry(list);
    ex_list_add(list, head);
}

/**
 * list_move_tail - delete from one list and add as another's tail
 * @list: the entry to move
 * @head: the head that will follow our entry
 */

/**
 * @brief ex_list_move_tail - 从一个链表中删除指定节点, 并添加为另一个链表的尾节点.
 *
 * @param list 要移动的节点.
 * @param head list 节点进入之后的头节点.
 */
static inline void ex_list_move_tail(ex_list_t *list, ex_list_t *head)
{
    __ex_list_del_entry(list);
    ex_list_add_tail(list, head);
}

/**
 * list_is_last - tests whether @list is the last entry in list @head
 * @list: the entry to test
 * @head: the head of the list
 */

/**
 * @brief ex_list_is_last - 测试 list 是否是链表 head 中的最后一个节点.
 *
 * @param list 要测试的节点.
 * @param head 链表头.
 * @return int
 * - 1          是最后一个节点
 * - 0          不是最后一个节点
 */
static inline int ex_list_is_last(const ex_list_t *list, const ex_list_t *head)
{
    return list->next == head;
}

/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */

/**
 * @brief ex_list_empty - 测试链表是否为空.
 *
 * @param head 要测试的链表头节点.
 * @return int
 * - 1          空表
 * - 0          非空表
 */
static inline int ex_list_empty(const ex_list_t *head)
{
    return head->next == head;
}

/**
 * ex_list_empty_careful - tests whether a list is empty and not being modified
 * @head: the list to test
 *
 * Description:
 * tests whether a list is empty _and_ checks that no other CPU might be
 * in the process of modifying either member (next or prev)
 *
 * NOTE: using ex_list_empty_careful() without synchronization
 * can only be safe if the only activity that can happen
 * to the list entry is ex_list_del_init(). Eg. it cannot be used
 * if another CPU could re-ex_list_add() it.
 */

/**
 * @brief ex_list_empty_careful - 测试链表是否为空且未被修改.
 *
 * 测试链表是否为空并检查是否没有其他 CPU 正在修改任一成员（下一个或上一个）.
 *
 * @attention 不同步地使用 ex_list_empty_careful(),
 * 只有在 ex_list_del_init() 是链表节点唯一可能发生的活动时才是安全的.
 * 例如, 如果另一个 CPU 可以重新添加 ex_list_add(), 则不能使用该函数.
 *
 * @param head 要测试的链表头节点.
 * @return int
 * - 1          为空且未被修改
 * - 0          不为空或正在被修改
 */
static inline int ex_list_empty_careful(const ex_list_t *head)
{
    ex_list_t *next = head->next;
    return (next == head) && (next == head->prev);
}

/**
 * list_rotate_left - rotate the list to the left
 * @head: the head of the list
 */

/**
 * @brief ex_list_rotate_left - 将链表向左旋转.
 *
 * @param head 链表头节点.
 */
static inline void ex_list_rotate_left(ex_list_t *head)
{
    ex_list_t *first;

    if (!ex_list_empty(head)) {
        first = head->next;
        ex_list_move_tail(first, head);
    }
}

/**
 * list_is_singular - tests whether a list has just one entry.
 * @head: the list to test.
 */

/**
 * @brief ex_list_is_singular - 测试链表是否只有一个节点.
 *
 * @param head 链表头节点.
 * @return int
 * - 1          只有一个节点
 * - 0          不只有一个节点
 */
static inline int ex_list_is_singular(const ex_list_t *head)
{
    return !ex_list_empty(head) && (head->next == head->prev);
}

static inline void __ex_list_cut_position(
    ex_list_t *list, ex_list_t *head, ex_list_t *entry)
{
    ex_list_t *new_node_first   = entry->next;
    list->next                  = head->next;
    list->next->prev            = list;
    list->prev                  = entry;
    entry->next                 = list;
    head->next                  = new_node_first;
    new_node_first->prev        = head;
}

/**
 * ex_list_cut_position - cut a list into two
 * @list: a new_node list to add all removed entries
 * @head: a list with entries
 * @entry: an entry within head, could be the head itself
 *  and if so we won't cut the list
 *
 * This helper moves the initial part of @head, up to and
 * including @entry, from @head to @list. You should
 * pass on @entry an element you know is on @head. @list
 * should be an empty list or a list you do not care about
 * losing its data.
 *
 */

/**
 * @brief ex_list_cut_position - 将链表切成两部分.
 *
 * 该辅助函数将 head 的初始部分（包括 entry 在内）从 head 移至 list.
 * 你应该在 entry 中传递一个你知道在 head 中的元素.
 * list 应该是一个空链表, 或者是一个你不希望丢失数据的链表.
 *
 * @param list 一个 new_node 链表, 用于添加所有已删除的节点.
 * @param head 包含节点的链表
 * @param entry head 中的一个节点, 可以是 head 本身, 如果这样, 则不会删除该链表.
 */
static inline void ex_list_cut_position(
    ex_list_t *list, ex_list_t *head, ex_list_t *entry)
{
    if (ex_list_empty(head)) {
        return;
    }
    if (ex_list_is_singular(head)
            && (head->next != entry && head != entry)) {
        return;
    }
    if (entry == head) {
        ex_list_init(list);
    } else {
        __ex_list_cut_position(list, head, entry);
    }
}

static inline void __ex_list_splice(
    const ex_list_t *list, ex_list_t *prev, ex_list_t *next)
{
    ex_list_t *first = list->next;
    ex_list_t *last = list->prev;

    first->prev = prev;
    prev->next = first;

    last->next = next;
    next->prev = last;
}

/**
 * ex_list_splice - join two lists, this is designed for stacks
 * @list: the new_node list to add.
 * @head: the place to add it in the first list.
 */

/**
 * @brief ex_list_splice - 连接两个链表, 这是为栈设计的.
 *
 * @param list 要添加的 new_node 链表.
 * @param head 将其添加到第一个链表中的位置.
 */
static inline void ex_list_splice(
    const ex_list_t *list, ex_list_t *head)
{
    if (!ex_list_empty(list)) {
        __ex_list_splice(list, head, head->next);
    }
}

/**
 * ex_list_splice_tail - join two lists, each list being a queue
 * @list: the new_node list to add.
 * @head: the place to add it in the first list.
 */

/**
 * @brief ex_list_splice_tail - 连接两个链表, 每个链表都是一个队列
 *
 * @param list 要添加的 new_node 链表.
 * @param head 将其添加到第一个链表中的位置.
 */
static inline void ex_list_splice_tail(ex_list_t *list, ex_list_t *head)
{
    if (!ex_list_empty(list)) {
        __ex_list_splice(list, head->prev, head);
    }
}

/**
 * ex_list_splice_init - join two lists and reinitialise the emptied list.
 * @list: the new_node list to add.
 * @head: the place to add it in the first list.
 *
 * The list at @list is reinitialised
 */

/**
 * @brief ex_list_splice_init - 连接两个链表并重新初始化空链表.
 *
 * list 处的链表被重新初始化.
 *
 * @param list 要添加的 new_node 链表.
 * @param head 将其添加到第一个链表中的位置.
 */
static inline void ex_list_splice_init(ex_list_t *list, ex_list_t *head)
{
    if (!ex_list_empty(list)) {
        __ex_list_splice(list, head, head->next);
        ex_list_init(list);
    }
}

/**
 * ex_list_splice_tail_init - join two lists and reinitialise the emptied list
 * @list: the new_node list to add.
 * @head: the place to add it in the first list.
 *
 * Each of the lists is a queue.
 * The list at @list is reinitialised
 */

/**
 * @brief ex_list_splice_tail_init - 连接两个链表并重新初始化空链表.
 *
 * 每个链表都是一个队列.
 * list 处的链表被重新初始化.
 *
 * @param list 要添加的 new_node 链表.
 * @param head 将其添加到第一个链表中的位置.
 */
static inline void ex_list_splice_tail_init(ex_list_t *list, ex_list_t *head)
{
    if (!ex_list_empty(list)) {
        __ex_list_splice(list, head->prev, head);
        ex_list_init(list);
    }
}

/* ==================== [Macros] ============================================ */

/**
 * @brief ex_list_entry - 获取节点的结构体.
 *
 * 从包含链表节点的结构体中获得结构体指针.
 *
 * @param ptr 指向成员的指针.
 * @param type 包含 ex_list_t 的结构体类型.
 * @param member 结构中成员 list_struct 的名称.
 * @return 结构体的地址.
 */
#define ex_list_entry(ptr, type, member) \
    ex_container_of(ptr, type, member)


/**
 * @brief ex_list_first_entry - 获取链表中的第一个元素.
 *
 * 请注意，该链表不应为空.
 *
 * @param ptr 链表头.
 * @param type 包含 ex_list_t 的结构体类型.
 * @param member 结构中成员 list_struct 的名称.
 * @return 结构体的地址.
 */
#define ex_list_first_entry(ptr, type, member) \
    ex_list_entry((ptr)->next, type, member)


/**
 * @brief ex_list_for_each - 迭代链表.
 *
 * @param pos 迭代游标 &ex_list_t.
 * @param head 链表头.
 */
#define ex_list_for_each(pos, head) \
    for ((pos) = (head)->next; (pos) != (head); (pos) = (pos)->next)


/**
 * @brief __ex_list_for_each - 迭代链表.
 *
 * 此变体与 ex_list_for_each() 不再有区别。
 *
 * @param pos 迭代游标 &ex_list_t.
 * @param head 链表头.
 */
#define __ex_list_for_each(pos, head) \
    for ((pos) = (head)->next; (pos) != (head); (pos) = (pos)->next)


/**
 * @brief ex_list_for_each_prev - 反向迭代链表.
 *
 * @param pos 迭代游标 &ex_list_t.
 * @param head 链表头.
 */
#define ex_list_for_each_prev(pos, head) \
    for ((pos) = (head)->prev; (pos) != (head); (pos) = (pos)->prev)


/**
 * @brief ex_list_for_each_safe - 迭代链表的安全版本, 防止删除链表节点时可能出现的问题.
 *
 * @param pos 迭代游标 &ex_list_t.
 * @param n 另一个 &ex_list_t 用于临时存储.
 * @param head 链表头.
 */
#define ex_list_for_each_safe(pos, n, head) \
    for ((pos) = (head)->next, (n) = (pos)->next; (pos) != (head); \
         (pos) = (n), (n) = (pos)->next)


/**
 * @brief ex_list_for_each_safe - 方向迭代链表的安全版本, 防止删除链表节点时可能出现的问题.
 *
 * @param pos 迭代游标 &ex_list_t.
 * @param n 另一个 &ex_list_t 用于临时存储.
 * @param head 链表头.
 */
#define ex_list_for_each_prev_safe(pos, n, head) \
    for ((pos) = (head)->prev, (n) = (pos)->prev; \
         (pos) != (head); \
         (pos) = (n), (n) = (pos)->prev)

/**
 * @attention 注意, 由于移除了 GUN 的 `typeof`,
 * 以下带有 `_entry` 后缀的宏都必须显式写出包含链表的结构体的类型，
 * 详情见 @ref ex_container_of.
 *
 * pos 和 n 的数据类型必须相同!
 */


/**
 * @brief 从头到尾遍历给定的结构体对象
 *
 * @param pos 每次迭代获取到的结构体对象（是type类型）
 * @param head 链表的头节点
 * @param type 结构体的类型
 * @param member 链表在结构体中的成员名
 */
#define ex_list_for_each_entry(pos, head, type, member) \
    for ((pos) = ex_list_entry((head)->next, type, member); \
         &(pos)->member != (head); \
         (pos) = ex_list_entry((pos)->member.next, type, member))

/**
 * @brief 从尾到头遍历给定的结构体对象
 *
 * @param pos 每次迭代获取到的结构体对象（是type类型）
 * @param head 链表的头节点
 * @param type 结构体的类型
 * @param member 链表在结构体中的成员名
 */
#define ex_list_for_each_entry_reverse(pos, head, type, member) \
    for ((pos) = ex_list_entry((head)->prev, type, member); \
         &(pos)->member != (head); \
         (pos) = ex_list_entry((pos)->member.prev, type, member))


/**
 * @brief 在ex_list_for_each_entry_continue调用之前，确保传入的pos有效
 *          如果pos不存在，则从头强制拓展一个pos参数
 *
 * @param pos 每次迭代获取到的结构体对象（是type类型）
 * @param head 链表的头节点
 * @param type 结构体的类型
 * @param member 链表在结构体中的成员名
 */
#define ex_list_prepare_entry(pos, head, type, member) \
    ((pos) ? : ex_list_entry(head, type, member))

/**
 * @brief 遍历没有遍历完的链表（迭代不包括当前值）
 *
 * @param pos 每次迭代获取到的结构体对象（是type类型）
 * @param head 链表的头节点
 * @param type 结构体的类型
 * @param member 链表在结构体中的成员名
 */
#define ex_list_for_each_entry_continue(pos, head, type, member) \
    for ((pos) = ex_list_entry((pos)->member.next, type, member); \
         &(pos)->member != (head); \
         (pos) = ex_list_entry((pos)->member.next, type, member))

/**
 * @brief 遍历之前遍历过的链表（迭代不包括当前值且顺序相反）
 *
 * @param pos 每次迭代获取到的结构体对象（是type类型）
 * @param head 链表的头节点
 * @param type 结构体的类型
 * @param member 链表在结构体中的成员名
 */
#define ex_list_for_each_entry_continue_reverse(pos, head, type, member) \
    for ((pos) = ex_list_entry((pos)->member.prev, type, member); \
         &(pos)->member != (head); \
         (pos) = ex_list_entry((pos)->member.prev, type, member))

/**
 * @brief 遍历没有遍历完的链表（迭代包括当前值）
 *
 * @param pos 每次迭代获取到的结构体对象（是type类型）
 * @param head 链表的头节点
 * @param type 结构体的类型
 * @param member 链表在结构体中的成员名
 */
#define ex_list_for_each_entry_from(pos, head, type, member) \
    for (; &(pos)->member != (head); \
         (pos) = ex_list_entry((pos)->member.next, type, member))

/**
 * @brief 遍历的安全版本，提供一个n缓存下一个值。使用时不使用n而使用
 *  当我们需要在遍历的过程中删除链表成员时，请调用它以保证链表后续迭代正确
 *
 * @param pos 每次迭代获取到的结构体对象（是type类型）
 * @param n 每次迭代缓存的结构体对象(是type类型)
 * @param head 链表的头节点
 * @param type 结构体的类型
 * @param member 链表在结构体中的成员名
 */
#define ex_list_for_each_entry_safe(pos, n, head, type, member) \
    for ((pos) = ex_list_entry((head)->next, type, member), \
         (n) = ex_list_entry((pos)->member.next, type, member); \
         &(pos)->member != (head); \
         (pos) = (n), (n) = ex_list_entry(n->member.next, type, member))

/**
 * @brief 遍历没有遍历完的链表（迭代不包括当前值）的安全版本，提供一个n缓存下一个值。使用时不使用n而使用
 *  当我们需要在遍历的过程中删除链表成员时，请调用它以保证链表后续迭代正确
 *
 * @param pos 每次迭代获取到的结构体对象（是type类型）
 * @param n 每次迭代缓存的结构体对象(是type类型)
 * @param head 链表的头节点
 * @param type 结构体的类型
 * @param member 链表在结构体中的成员名
 */
#define ex_list_for_each_entry_safe_continue(pos, n, head, type, member) \
    for ((pos) = ex_list_entry((pos)->member.next, type, member), \
         (n) = ex_list_entry((pos)->member.next, type, member); \
         &(pos)->member != (head); \
         (pos) = (n), (n) = ex_list_entry((n)->member.next, type, member))

/**
 * @brief 遍历没有遍历完的链表（迭代包括当前值）的安全版本，提供一个n缓存下一个值。使用时不使用n而使用
 *  当我们需要在遍历的过程中删除链表成员时，请调用它以保证链表后续迭代正确
 *
 * @param pos 每次迭代获取到的结构体对象（是type类型）
 * @param n 每次迭代缓存的结构体对象(是type类型)
 * @param head 链表的头节点
 * @param type 结构体的类型
 * @param member 链表在结构体中的成员名
 */
#define ex_list_for_each_entry_safe_from(pos, n, head, type, member) \
    for ((n) = ex_list_entry((pos)->member.next, type, member); \
         &(pos)->member != (head); \
         (pos) = (n), (n) = ex_list_entry((n)->member.next, type, member))

/**
 * @brief 反向遍历的安全版本，提供一个n缓存下一个值。使用时不使用n而使用
 *  当我们需要在遍历的过程中删除链表成员时，请调用它以保证链表后续迭代正确
 *
 * @param pos 每次迭代获取到的结构体对象（是type类型）
 * @param n 每次迭代缓存的结构体对象(是type类型)
 * @param head 链表的头节点
 * @param type 结构体的类型
 * @param member 链表在结构体中的成员名
 */
#define ex_list_for_each_entry_safe_reverse(pos, n, head, type, member) \
    for ((pos) = ex_list_entry((head)->prev, type, member), \
         (n) = ex_list_entry((pos)->member.prev, type, member); \
         &(pos)->member != (head); \
         (pos) = (n), (n) = ex_list_entry((n)->member.prev, type, member))

/**
 * @brief 重置缓存n中下个节点
 *
 * @param pos 每次迭代获取到的结构体对象（是type类型）
 * @param n 每次迭代缓存的结构体对象(是type类型)
 * @param head 链表的头节点
 * @param type 结构体的类型
 * @param member 链表在结构体中的成员名
 */
#define ex_list_safe_reset_next(pos, n, type, member) \
    (n) = ex_list_entry((pos)->member.next, type, member)




#ifdef __cplusplus
}/* extern C */
#endif






#endif // _EXLIST_H_
