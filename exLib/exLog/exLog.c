/**
 * @file exLog.c
 * @author ZC (387646983@qq.com)
 * @brief ex日志工具
 * @version 0.1
 * @date 2024-11-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */


/* ==================== [Includes] ========================================== */
#include "exLog_cfg.h"

#if EX_LOG_DUMP_IS_ENABLE

#include "exLog.h"
/* ==================== [Defines] ========================================== */
/* 只输出 16 进制格式数据时，每行实际会输出的字节数 */
#define EX_DUMP_HEX_BYTES_PER_LINE                  (53)
/* 输出 16 进制格式数据和 ASCII 字符时，每行实际会输出的字节数 */
#define EX_DUMP_HEX_ASCII_BYTES_PER_LINE            (72)
/* 输出 16 进制格式数据、 ASCII 字符、转义字符时，每行实际会输出的字节数 */
#define EX_DUMP_HEX_ASCII_ESCAPE_BYTES_PER_LINE     (104)
/* 表头字节数，可能会多几个字节 */
#define EX_DUMP_TABLE_HEADER_BYTES                  (332)
/* ==================== [Typedefs] ========================================== */

/* ==================== [Static Prototypes] ========================================== */

/* ==================== [Global Prototypes] ========================================== */

/* ==================== [Static Variables] ========================================== */

/* ==================== [Static Functions] ================================== */

/* ==================== [Macros] ============================================ */

/* ==================== [Global Functions] ================================== */
ex_err_t ex_dump_mem(void *addr, size_t size, uint8_t flags_mask)
{
    if ((!addr) || (size == 0)) {
        ex_log_dump_printf("Invalid memory block\n");
        return EX_ERR_INVALID_ARG;
    }

    // 每行输出的内存字节数，不等于实际输出字节
    const uint8_t bytes_mem_out_per_line = 16;

    // 每行实际输出字节数
    uint8_t bytes_actually_out_per_line = 0;
    if (!BIT_GET(flags_mask, EX_DUMP_ASCII_BIT)) {
        bytes_actually_out_per_line = EX_DUMP_HEX_BYTES_PER_LINE;
    } else if (BIT_GET(flags_mask, EX_DUMP_ASCII_BIT)
               && !BIT_GET(flags_mask, EX_DUMP_ESCAPE_BIT)) {
        bytes_actually_out_per_line = EX_DUMP_HEX_ASCII_BYTES_PER_LINE;
    } else if (BIT_GET(flags_mask, EX_DUMP_ASCII_BIT)
               && BIT_GET(flags_mask, EX_DUMP_ESCAPE_BIT)) {
        bytes_actually_out_per_line = EX_DUMP_HEX_ASCII_ESCAPE_BYTES_PER_LINE;
    }

    // 打印内存块的起始地址
    ex_log_dump_printf("MEMORY START ADDRESS: %p, OUTPUT %d BYTES.\n", addr, (int)size);

    // 打印表头
    if (BIT_GET(flags_mask, EX_DUMP_HEAD_BIT)) {
        for (uint8_t i = 0; i < bytes_actually_out_per_line; i++) {
            ex_log_dump_printf("-");
        }
        ex_log_dump_printf("\n");
        ex_log_dump_printf(" OFS  "); // 偏移 offset
        for (uint8_t i = 0; i < bytes_mem_out_per_line; i++) {
            ex_log_dump_printf("%2X ", i);
        }
        if (BIT_GET(flags_mask, EX_DUMP_ASCII_BIT)) {
            ex_log_dump_printf("| ASCII");
        }
        ex_log_dump_printf("\n");
        for (uint8_t i = 0; i < bytes_actually_out_per_line; i++) {
            ex_log_dump_printf("-");
        }
        ex_log_dump_printf("\n");
    }

    uint8_t byte = 0; // 当前地址的字节的值
    // 遍历内存块中
    for (size_t i = 0; i < size; i++) {
        byte = *((uint8_t *)addr + i);

        if (i % bytes_mem_out_per_line == 0) {
            // 每行的开头打印行号
            ex_log_dump_printf("%04lu: ", (unsigned long)(i / bytes_mem_out_per_line));
        }

        ex_log_dump_printf("%02X ", byte); // 打印当前地址的字节的值的十六进制

        // 如果达到每行显示的字节数，
        // 或者已经是最后一个字节，就打印 ASCII 字符串
        if (((i + 1) % bytes_mem_out_per_line == 0) || (i == size - 1)) {
            // 如果不是每行显示的字节数，就补齐空格
            if ((i + 1) % bytes_mem_out_per_line != 0) {
                for (size_t j = 0;
                        j < (bytes_mem_out_per_line - (i + 1) % bytes_mem_out_per_line) * 3;
                        j++) {
                    ex_log_dump_printf(" ");
                }
            }
            // 遍历输出 ASCII
            if (BIT_GET(flags_mask, EX_DUMP_ASCII_BIT)) {
                ex_log_dump_printf("| ");
                for (size_t j = i - i % bytes_mem_out_per_line; j <= i; j++) {
                    uint8_t b = *((uint8_t *)addr + j);
                    if (b >= ' ' && b <= '~') { // 可见字符
                        if (BIT_GET(flags_mask, EX_DUMP_ESCAPE_BIT)) {
                            ex_log_dump_printf(" ");
                        }
                        ex_log_dump_printf("%c", b);
                        if (BIT_GET(flags_mask, EX_DUMP_ESCAPE_BIT)) {
                            ex_log_dump_printf(" ");
                        }
                    } else if (BIT_GET(flags_mask, EX_DUMP_ESCAPE_BIT)) {
                        // 显示转义字符
                        switch (b) {
                        case '\0': ex_log_dump_printf("\\0 "); break; // 空字符
                        case '\a': ex_log_dump_printf("\\a "); break; // 响铃符
                        case '\b': ex_log_dump_printf("\\b "); break; // 退格符
                        case '\t': ex_log_dump_printf("\\t "); break; // 水平制表符
                        case '\n': ex_log_dump_printf("\\n "); break; // 换行符
                        case '\v': ex_log_dump_printf("\\v "); break; // 垂直制表符
                        case '\f': ex_log_dump_printf("\\f "); break; // 换页符
                        case '\r': ex_log_dump_printf("\\r "); break; // 回车符
                        // 其他不可打印字符，用十六进制表示
                        default: ex_log_dump_printf("%02x ", b); break;
                        }
                    } else {
                        // 转义字符外的不可见字符
                        ex_log_dump_printf(".");
                        if (BIT_GET(flags_mask, EX_DUMP_ESCAPE_BIT)) {
                            ex_log_dump_printf("  ");
                        }
                    } /* else: 非转义字符 */
                } /* for: 输出 ASCII */
            } /* if: 需要输出 ASCII */
            ex_log_dump_printf("\n");
        } /* if: 需要输出 ASCII 或空格 */
    } /* for: 0 ~ size */
    /* 表尾 */
    if (BIT_GET(flags_mask, EX_DUMP_TAIL_BIT)) {
        for (uint8_t i = 0; i < bytes_actually_out_per_line; i++) {
            ex_log_dump_printf("-");
        }
        ex_log_dump_printf("\n");
    }
    return EX_OK;
}

#endif /* EX_LOG_DUMP_IS_ENABLE */

