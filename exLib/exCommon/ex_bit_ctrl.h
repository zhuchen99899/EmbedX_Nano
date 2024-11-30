/**
 * @file ex_bit_ctrl.h
 * @author ZC (387646983@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-11-28
 * @note 位操作库
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _EXBITCTRL_H_
#define _EXBITCTRL_H_



/* ==================== [Includes] ========================================== */


#ifdef __cplusplus
extern "C" {
#endif


/* ==================== [Defines] ========================================== */

/* ==================== [Macros] ============================================ */
#ifndef __ASSEMBLER__
#ifndef BIT
#define BIT(nr)                 (1UL << (nr))
#endif
#ifndef BIT64
#define BIT64(nr)               (1ULL << (nr))
#endif
#else /* defined (__ASSEMBLER__) */
#ifndef BIT
#define BIT(nr)                 (1 << (nr))
#endif
#endif /* __ASSEMBLER__ */

/**
 * @brief 32 位位操作宏（一个位）。
 */
#ifndef BIT_SET0
/**
 * @brief 设置 32 位变量 var 的 bit_n 为 0。
 *
 * @param variable 被读写的变量。
 * @param n 比特下标，从 0 开始。
 */
#define BIT_SET0(var, n) ((var) &= ~BIT(n))
#endif

#ifndef BIT_SET1
/**
 * @brief 设置 32 位变量 var 的 bit_n 为 1。
 *
 * @param variable 被读写的变量。
 * @param n 比特下标，从 0 开始。
 */
#define BIT_SET1(var, n) ((var) |= BIT(n))
#endif

#ifndef BIT_SET
/**
 * @brief 设置 32 位变量 var 的 bit_n 为 value。
 *
 * @param variable 被读写的变量。
 * @param n 比特下标，从 0 开始。
 */
#define BIT_SET(var, n, value) \
    ((value) ? BIT_SET1((var), (n)) : BIT_SET0((var), (n)))
#endif

#ifndef BIT_FLIP
/**
 * @brief 翻转 32 位变量 var 的 bit_n。
 *
 * @param variable 被翻转的变量。
 * @param n 比特下标，从 0 开始。
 */
#define BIT_FLIP(var, n) ((var) ^= BIT(n))
#endif

#ifndef BIT_GET
/**
 * @brief 获取 32 位源 src 的 bit_n。
 *
 * @param variable 被读取的变量。
 * @param n 比特下标，从 0 开始。
 *
 * @return src 的 bit_n 上的值。
 */
#define BIT_GET(src, n) (((src) & BIT(n)) >> (n))
#endif

#ifndef BIT_GET_MODIFY0
/**
 * @brief 获取将 32 位源 src 的 bit_n 置 0 后的值。
 *
 * @param variable 被读取的变量。
 * @param n 比特下标，从 0 开始。
 *
 * @return 32 位 src 的 bit_n 置 0 后的值。
 */
#define BIT_GET_MODIFY0(src, n) ((src) & ~BIT(n))
#endif

#ifndef BIT_GET_MODIFY1
/**
 * @brief 获取将 32 位源 src 的 bit_n 置 1 后的值。
 *
 * @param variable 被读取的变量。
 * @param n 比特下标，从 0 开始。
 *
 * @return 32 位 src 的 bit_n 置 1 后的值。
 */
#define BIT_GET_MODIFY1(src, n) ((src) | BIT(n))
#endif

#ifndef BIT_GET_MODIFY
/**
 * @brief 获取将 32 位源 src 的 bit_n 置 value 后的值。
 *
 * @param variable 被读取的变量。
 * @param n 比特下标，从 0 开始。
 * @param value 0 或 1。
 *
 * @return 32 位 src 的 bit_n 置 value 后的值。
 */
#define BIT_GET_MODIFY(src, n, value) \
    ((value) ? BIT_GET_MODIFY1((src), (n)) : BIT_GET_MODIFY0((src), (n)))
#endif

#ifndef BIT_GET_MODIFY_FLIP
/**
 * @brief 获取翻转 32 位源 src 的 bit_n 后的值。
 *
 * @param variable 被读取的变量。
 * @param n 比特下标，从 0 开始。
 *
 * @return 翻转 32 位 src 的 bit_n 后的值。
 */
#define BIT_GET_MODIFY_FLIP(src, n) ((src) ^ BIT(n))
#endif

/**
 * @brief 32 位位操作宏（多位）。
 */
#ifndef BITS_MASK
/**
 * @brief 获取低 n 位为 1 的位掩码。
 *
 * @param n 小于等于 32 的数。
 *
 * @return 低 n 位为 1 的位掩码。
 *
 * @example
 * BITS_MASK(6)  == 0x003f ==          0b00111111
 * BITS_MASK(13) == 0x1fff == 0b00011111 11111111
 */
#define BITS_MASK(n) (((n) < 32) ? (BIT(n) - 1) : (~0UL))
#endif

#ifndef BITS_SET0
/**
 * @brief 设置 32 位变量 var 的对应位掩码 bits_mask 为 1 的地方为 0。
 *
 * @param var 被设置的变量。
 * @param bits_mask 位掩码。注意！为 1 的位表示需要被设为 0 的位。
 *
 * @note
 * 1. 位掩码为 1 的位表示需要被设为 0 的位。
 *
 * @example
 * uint32_t var = 0xffff;
 * BITS_SET0(var, 0b0011 0110 0101 1010) == 0b11001001 10100101
 * var = 0xffff;
 * BITS_SET0(var, BITS_MASK(4) << 3)     == 0b11111111 10000111
 */
#define BITS_SET0(var, bits_mask) ((var) &= ~(bits_mask))
#endif

#ifndef BITS_SET1
/**
 * @brief 设置 32 位变量 var 的对应位掩码 bits_mask 为 1 的地方为 1。
 *
 * @param var 被设置的变量。
 * @param bits_mask 位掩码。注意！为 1 的位表示需要被设为 1 的位。
 *
 * @note
 * 1. 位掩码为 1 的位表示需要被设为 1 的位。
 *
 * @example
 * uint32_t var = 0x0000;
 * BITS_SET1(var, 0b0011 0110 0101 1010) == 0b00110110 01011010
 * var = 0x0000;
 * BITS_SET1(var, BITS_MASK(4) << 3)     == 0b00000000 01111000
 */
#define BITS_SET1(var, bits_mask) ((var) |= (bits_mask))
#endif

#ifndef BITS_FLIP
/**
 * @brief 翻转 32 位变量 var 的 bits_mask 为 1 的位。
 *
 * @param var 被设置的变量。
 * @param bits_mask 位掩码。注意！为 1 的位表示需要被翻转的位。
 *
 * @note
 * 1. 位掩码为 1 的位表示需要被翻转的位。
 */
#define BITS_FLIP(var, bits_mask) ((var) ^= (bits_mask))
#endif

#ifndef BITS_GET
/**
 * @brief 获取 32 位 src 内，从 offset 位起，共 n 位数据。
 *
 * @param src 被读取的源。
 * @param n 需要读取 n 位。
 * @param offset 偏移量。从 bit0 起计算。
 *
 * @return 32 位源 src 内，从 offset 位起，共 n 位数据。
 *
 * @example
 * BITS_GET(0b0011 1010 1111 0010, 7, 5) == 0x57 == 0b01010111
 *
 * bit:                54 3210  : bit == 5
 * src:  0b0011 1010 1111 0010  : src == 0x3af2
 *              ↓      ↓
 * num:         7654 321        : n   == 7
 * ————————————————————————————————————————————
 * ret:     0b0 1010 111        : ret == 0x57
 */
#define BITS_GET(src, n, offset) (((src) & (BITS_MASK(n) << (offset))) >> (offset))
#endif

#ifndef BITS_CHECK
/**
 * @brief 检查变量 var 在 bits_mask 的位置上是否存在 1。
 *
 * @param var 待检查的变量。
 * @param bits_mask 位掩码。注意！为 1 的位表示需要检查的位。
 *
 * @note
 * 1. 位掩码为 1 的位表示需要检查的位。
 */
#define BITS_CHECK(src, bits_mask) (!!((src) & (bits_mask)))
#endif

#ifndef BITS_GET_MODIFY
/**
 * @brief 将 32 位 src 的 offset 位起 n 位修改为 value 并返回（不修改 src）。
 *
 * @param src 被读取的源。
 * @param n 需要修改的位数。
 * @param offset 偏移量。从 bit0 起计算。
 * @param value src 的 offset 位起 n 位源需要修改到的目标值。
 *
 * @return 32 位 src 的 offset 位起 n 位修改为 value 的值。
 *
 * @example
 *  BITS_GET_MODIFY(src       , n, offset, value     )
 *  BITS_GET_MODIFY(0x4c5ca6d2, 8, 13    , 0b10101111)
 *
 *  src:    0100 1100 0101 1100 1010 0110 1101 0010 == 0x4c5ca6d2
 *                       1 0101 111                 == (value << 13)
 *                       ↓ ↓↓↓↓ ↓↓↓
 *  ret:    0100 1100 0101 0101 1110 0110 1101 0010 == 0x4c55e6d2
 *
 * @details
 *          0100 1100 0101 1100 1010 0110 1101 0010   <=  src
 *       ^  0000 0000 0001 0101 1110 0000 0000 0000   <=  ((BITS_MASK(n) & (value)) << (offset))
 *      ————————————————————————————————————————————————
 *          0100 1100 0100 1001 0100 0110 1101 0010
 *
 *          0100 1100 0100 1001 0100 0110 1101 0010       ans
 *       &  0000 0000 0001 1111 1110 0000 0000 0000   <=  (BITS_MASK(n) << 13)
 *      ————————————————————————————————————————————————
 *          0000 0000 0000 1001 0100 0000 0000 0000
 *
 *          0000 0000 0000 1001 0100 0000 0000 0000       ans
 *       ^  0100 1100 0101 1100 1010 0110 1101 0010   <=  src
 *      ————————————————————————————————————————————————
 *          0100 1100 0101 0101 1110 0110 1101 0010   =>  ret
 *
 * @note
 * 1. n + offset 不要大于 32 位。
 */
#define BITS_GET_MODIFY(src, n, offset, value) \
    ((((src) ^ ((BITS_MASK(n) & (value)) << (offset))) \
             & (BITS_MASK(n) << (offset))) \
             ^ (src))
#endif

#ifndef BITS_SET
/**
 * @brief 设置 32 位 src 的 offset 位起 n 位为 value。
 *
 * @see BITS_GET_MODIFY @ref BITS_GET_MODIFY
 * @note
 * 1. n + offset 不要大于 32 位。
 */
#define BITS_SET(src, n, offset, value) \
    ((src) = BITS_GET_MODIFY((src), (n), (offset), (value)))
#endif
/* ==================== [Typedefs] ========================================== */

/* ==================== [Public Prototypes] ========================================== */

#ifdef __cplusplus
}/* extern C */
#endif


#endif // _EXBITCTRL_H_
