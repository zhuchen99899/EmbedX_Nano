/**
 * @file ex_export_section_sort.c
 * @author ZC (387646983@qq.com)
 * @brief  export初始化组件 sort section 方法
 * @version 0.1
 * @date 2024-12-01
 * @note export初始化组件 sort section 方法，此方法默认section段会进行sort排序，需要编译器支持如keil
 * @copyright Copyright (c) 2024
 * 
 */
/* ==================== [Includes] ========================================== */
#include "ex_export_section.h"
/* ==================== [Defines] ========================================== */
#if EX_EXPROT_METHOD == EX_EXPORT_BY_SORT_SECTION

EX_TAG("ex_export_sec");
/* ==================== [Macros] ============================================ */

/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ========================================== */
static ex_export_t *export_init_table = NULL;
static uint32_t count_export_init = 0;
static int8_t export_level_max = INT8_MAX;
static void module_null_init(void)
{
    /* NULL */
}

INIT_EXPORT(module_null_init, EXPORT_LEVEL_BSP);

/* ==================== [Static Variables] ========================================== */

/* ==================== [Static Functions] ================================== */
/**
 * @brief Get the init export table.
 * 
 */
/* ==================== [Public Functions] ================================== */

static void section_get_init_export_table(void)
{   
    ex_export_t *func_block = (ex_export_t *)&init_module_null_init;
    ex_pointer_t address_last;
        
    while (1)
    { //向上寻找最新属于ex_export的函数
        address_last = ((ex_pointer_t)func_block - sizeof(ex_export_t));
        ex_export_t *table = (ex_export_t *)address_last;
        if (table->magic_head != EXPORT_INIT_MAGIC_ID ||
            table->magic_tail != EXPORT_INIT_MAGIC_ID)
        {
            break; //非ex_export section定义的函数，退出查找
        }
        func_block = table;
    }
    export_init_table = func_block; //ex_export section 段第一个函数

    uint32_t i = 0;
    while (1)
    {
        if (export_init_table[i].magic_head == EXPORT_INIT_MAGIC_ID &&
            export_init_table[i].magic_tail == EXPORT_INIT_MAGIC_ID)
        { //函数属于ex_export section 段
            if (export_init_table[i].level > export_level_max)
            {
                export_level_max = export_init_table[i].level; //超出最大定义等级
            }
            i ++; //记录
        }
        else
        {
            break;
        }
    }
    count_export_init = i;//记录属于ex_export section 段的函数总个数
}

/**
 * @brief execute_init_func_
 * 
 * @param level init_level
 */
static void section_init_func_execute(int8_t level)
{
    /* Execute the poll function in the specific level. */
    for (uint32_t i = 0; i < count_export_init; i ++)
    {
        if (export_init_table[i].level == level)
        {
                EX_LOGD("Export init  %s.\r\n", export_init_table[i].name);

                ((void (*)(void))export_init_table[i].func)();
        }
    }
}

/**
 * @brief export_section_sort_init
 * @note 只支持指定编译器section自动排序
 */
void ex_export_section_init(void)
{
    section_get_init_export_table();
    for (uint8_t level = 0; level < export_level_max; level ++) //执行所有初始等级的ex_export 段函数
    {
    
    section_init_func_execute(level);
    }

}

#endif