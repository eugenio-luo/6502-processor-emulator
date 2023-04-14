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
        LDA_INDX_INDR = 0xA1,
        LDX_IMM = 0xA2,
        LDA_ZERO = 0xA5,
        LDX_ZERO = 0xA6,
        LDA_IMM = 0xA9,
        LDA_ABS = 0xAD,
        LDX_ABS = 0xAE,
        LDA_INDR_INDY = 0xB1,
        LDA_ZEROX = 0xB5,
        LDX_ZEROY = 0xB6,
        LDA_ABSY = 0xB9,
        LDA_ABSX = 0xBD,
        LDX_ABSY = 0xBE,
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
