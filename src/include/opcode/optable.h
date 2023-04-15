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
        LDA_ABS = 0xAD,
        LDA_ABSX = 0xBD,
        LDA_ABSY = 0xB9,
        LDA_ZERO = 0xA5,
        LDA_ZEROX = 0xB5,
        LDA_INDX_INDR = 0xA1,
        LDA_INDR_INDY = 0xB1,

        LDX_IMM = 0xA2,
        LDX_ABS = 0xAE,
        LDX_ABSY = 0xBE,
        LDX_ZERO = 0xA6,
        LDX_ZEROY = 0xB6,

        LDY_IMM = 0xA0,
        LDY_ABS = 0xAC,
        LDY_ABSX = 0xBC,
        LDY_ZERO = 0xA4,
        LDY_ZEROX = 0xB4,

        STA_ABS = 0x8D,
        STA_ABSX = 0x9D,
        STA_ABSY = 0x99,
        STA_ZERO = 0x85,
        STA_ZEROX = 0x95,
        STA_INDX_INDR = 0x81,
        STA_INDR_INDY = 0x91,

        STX_ABS = 0x8E,
        STX_ZERO = 0x86,
        STX_ZEROY = 0x96,

        STY_ABS = 0x8C,
        STY_ZERO = 0x84,
        STY_ZEROX = 0x94,

        TAX = 0xAA,
        TAY = 0xA8,
        TSX = 0xBA,
        TXA = 0x8A,
        TXS = 0x9A,
        TYA = 0x98,

        PHA = 0x48,
        PHP = 0x08,
        PLA = 0x68,
        PLP = 0x28,

        ASL_ACC = 0x0A,
        ASL_ABS = 0x0E,
        ASL_ABSX = 0x1E,
        ASL_ZERO = 0x06,
        ASL_ZEROX = 0x16,

        LSR_ACC = 0x4A,
        LSR_ABS = 0x4E,
        LSR_ABSX = 0x5E,
        LSR_ZERO = 0x46,
        LSR_ZEROX = 0x56,
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
