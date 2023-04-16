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

        ROL_ACC = 0x2A,
        ROL_ABS = 0x2E,
        ROL_ABSX = 0x3E,
        ROL_ZERO = 0x26,
        ROL_ZEROX = 0x36,

        ROR_ACC = 0x6A,
        ROR_ABS = 0x6E,
        ROR_ABSX = 0x7E,
        ROR_ZERO = 0x66,
        ROR_ZEROX = 0x76,

        AND_IMM = 0x29,
        AND_ABS = 0x2D,
        AND_ABSX = 0x3D,
        AND_ABSY = 0x39,
        AND_ZERO = 0x25,
        AND_ZEROX = 0x35,
        AND_INDX_INDR = 0x21,
        AND_INDR_INDY = 0x31,

        BIT_ABS = 0x2C,
        BIT_ZERO = 0x24,

        EOR_IMM = 0x49,
        EOR_ABS = 0x4D,
        EOR_ABSX = 0x5D,
        EOR_ABSY = 0x59,
        EOR_ZERO = 0x45,
        EOR_ZEROX = 0x55,
        EOR_INDX_INDR = 0x41,
        EOR_INDR_INDY = 0x51,

        ORA_IMM = 0x09,
        ORA_ABS = 0x0D,
        ORA_ABSX = 0x1D,
        ORA_ABSY = 0x19,
        ORA_ZERO = 0x05,
        ORA_ZEROX = 0x15,
        ORA_INDX_INDR = 0x01,
        ORA_INDR_INDY = 0x11,

        ADC_IMM = 0x69,
        ADC_ABS = 0x6D,
        ADC_ABSX = 0x7D,
        ADC_ABSY = 0x79,
        ADC_ZERO = 0x65,
        ADC_ZEROX = 0x75,
        ADC_INDX_INDR = 0x61,
        ADC_INDR_INDY = 0x71,

        CMP_IMM = 0xC9,
        CMP_ABS = 0xCD,
        CMP_ABSX = 0xDD,
        CMP_ABSY = 0xD9,
        CMP_ZERO = 0xC5,
        CMP_ZEROX = 0xD5,
        CMP_INDX_INDR = 0xC1,
        CMP_INDR_INDY = 0xD1, 

        CPX_IMM = 0xE0,
        CPX_ABS = 0xEC,
        CPX_ZERO = 0xE4,

        CPY_IMM = 0xC0,
        CPY_ABS = 0xCC,
        CPY_ZERO = 0xC4,

        SBC_IMM = 0xE9,
        SBC_ABS = 0xED,
        SBC_ABSX = 0xFD,
        SBC_ABSY = 0xF9,
        SBC_ZERO = 0xE5,
        SBC_ZEROX = 0xF5,
        SBC_INDX_INDR = 0xE1,
        SBC_INDR_INDY = 0xF1, 
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
