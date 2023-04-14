#include "opcode/optable.h"
#include "opcode/opfunc.h"
#include "cpu/registers.h"

#define OPCODE(FUNC, ADDR_MODE, ARGS, CYCLES)         \
        {FUNC, ADDR_MODE, ARGS, CYCLES}

#define OP_TABLE_SIZE   0x100

static opcode_t op_table[OP_TABLE_SIZE] = {
        [LDA_IMM] = OPCODE(op_lda, IMM, 1, 2),
        [LDA_ABS] = OPCODE(op_lda, ABS, 2, 4),
        [LDA_ABSX] = OPCODE(op_lda, ABSX, 2, 4),
        [LDA_ABSY] = OPCODE(op_lda, ABSY, 2, 4),
        [LDA_ZERO] = OPCODE(op_lda, ZERO, 1, 3),
        [LDA_ZEROX] = OPCODE(op_lda, ZEROX, 1, 4),
        [LDA_INDX_INDR] = OPCODE(op_lda, INDX_INDR, 1, 6),
        [LDA_INDR_INDY] = OPCODE(op_lda, INDR_INDY, 1, 5),

        [LDX_IMM] = OPCODE(op_ldx, IMM, 1, 2),
        [LDX_ABS] = OPCODE(op_ldx, ABS, 2, 4),
        [LDX_ABSY] = OPCODE(op_ldx, ABSY, 2, 4),
        [LDX_ZERO] = OPCODE(op_ldx, ZERO, 1, 3),
        [LDX_ZEROY] = OPCODE(op_ldx, ZEROY, 1, 4),

        [LDY_IMM] = OPCODE(op_ldy, IMM, 1, 2),
        [LDY_ABS] = OPCODE(op_ldy, ABS, 2, 4),
        [LDY_ABSX] = OPCODE(op_ldy, ABSX, 2, 4),
        [LDY_ZERO] = OPCODE(op_ldy, ZERO, 1, 3),
        [LDY_ZEROX] = OPCODE(op_ldy, ZEROX, 1, 4),

        [STA_ABS] = OPCODE(op_sta, ABS, 2, 4),
        [STA_ABSX] = OPCODE(op_sta, ABSX, 2, 5),
        [STA_ABSY] = OPCODE(op_sta, ABSY, 2, 5),
        [STA_ZERO] = OPCODE(op_sta, ZERO, 1, 3),
        [STA_ZEROX] = OPCODE(op_sta, ZEROX, 1, 4),
        [STA_INDX_INDR] = OPCODE(op_sta, INDX_INDR, 1, 6),
        [STA_INDR_INDY] = OPCODE(op_sta, INDR_INDY, 1, 6),

        [STX_ABS] = OPCODE(op_stx, ABS, 2, 4),
        [STX_ZERO] = OPCODE(op_stx, ZERO, 1, 3),
        [STX_ZEROY] = OPCODE(op_stx, ZEROY, 1, 4),

        [STY_ABS] = OPCODE(op_sty, ABS, 2, 4),
        [STY_ZERO] = OPCODE(op_sty, ZERO, 1, 3),
        [STY_ZEROX] = OPCODE(op_sty, ZEROX, 1, 4),

        [TAX] = OPCODE(op_tax, IMPL, 0, 2),
};

opcode_t *
op_get(uint8_t idx)
{
        return &op_table[idx];
}

void
set_affected_flags(uint8_t val)
{
        reg_clear_flags(ZERO_FLAG | NEG_FLAG);
        if (val == 0)
                reg_set_flags(ZERO_FLAG);
        else if (val & 0x80)
                reg_set_flags(NEG_FLAG);
}
