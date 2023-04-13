#ifndef NES_OPTABLE_H
#define NES_OPTABLE_H

#include <stdint.h>

typedef enum {
        IMPL,
        ACC,
        IMM,
        ZERO,
        ZEROX,
        ZEROY,
        REL,
        ABS,
        ABSX,
        ABSY,
        INDR,
        INDX_INDR,
        INDR_INDY,
} addr_mode_t;

enum {
        LDA_IMM = 0xA9,
};

typedef int (*op_func_t)(addr_mode_t, uint8_t, uint8_t);

typedef struct {
        op_func_t func;
        addr_mode_t addr_mode;
        int args;
        int cycles;
} opcode_t;

opcode_t *op_get(uint8_t idx);

#endif
