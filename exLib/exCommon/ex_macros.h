/**
 * @file ex_macros.h
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-11-29
 * @note 通用宏 不依赖于编译器
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _EX_MACROS_H_
#define _EX_MACROS_H_



/* ==================== [Includes] ========================================== */
#include "ex_common_cfg.h"

#ifdef __cplusplus
extern "C" {
#endif


/* ==================== [Defines] ========================================== */



/* ==================== [Macros] ============================================ */

#ifndef UNUSED
/**
 * @brief 未使用的变量通过 UNUSED 防止编译器警告。
 */
#define UNUSED(x)                       do { (void)(x); } while(0)
#endif

#ifndef CONCAT
/**
 * @brief 拼接。
 */
#define CONCAT(a, b)                    a##b
#endif

#ifndef CONCAT3
/**
 * @brief 拼接 3 个参数。
 */
#define CONCAT3(a, b, c)                a##b##c
#endif


#ifndef offsetof
/**
 * @brief offsetof - 返回结构成员相对于结构开头的字节偏移量。
 */
#define offsetof(type, member) ((size_t)&((type *)0)->member)
#endif /* offsetof */


/**
 * @brief container_of - 通过结构体成员变量地址获取结构体的地址.
 *
 * @param ptr 指向成员的指针。
 * @param type 结构体类型。
 * @param member 结构中成员的名称。
 *
 * @return 结构体的地址。
 *
 * @example
 * @code{c}
 * typedef struct {
 *     int member1;
 *     char member2;
 *     float member3;
 * } struct_test_t;
 *
 * int main()
 * {
 *     struct_test_t stru = {
 *         .member1 = 0x12345678,
 *         .member2 = 0xAB,
 *         .member3 = -123.456f,
 *     };
 *     char *p_member2 = &stru.member2;
 *     struct_test_t *p_stru = container_of(p_member2, struct_test_t, member2);
 *     if ((p_stru->member1 != (int)0x12345678)
 *             || (p_stru->member2 != (char)0xAB)
 *             || ((p_stru->member3 - (-123.456f)) > 1e-6f)) {
 *         printf("container_of error!\n");
 *     } else {
 *         printf("container_of ok!\n");
 *     }
 * }
 * @endcode
 */

#ifndef container_of
#define container_of(pointer, type, member)                                    \
    ({                                                                         \
        void *__pointer = (void *)(pointer);                                   \
        ((type *)(__pointer - offsetof(type, member)));                        \
    })
#endif


#ifndef ARRAY_SIZE
/**
 * @brief ARRAY_SIZE - 获取数组 arr 中的元素数量。
 *
 * @param arr 待求的数组。(必须是数组，此处不进行判断)
 *
 * @return 数组元素个数。
 */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#endif
/* ==================== [Typedefs] ========================================== */

/* ==================== [Global Prototypes] ========================================== */

#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EXMACROS_H_
