#include "opcode/optable.h"
#include "opcode/opfunc.h"

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
};

opcode_t *
op_get(uint8_t idx)
{
        return &op_table[idx];
}
