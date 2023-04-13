#include "opcode/optable.h"
#include "opcode/opfunc.h"

#define OPCODE(FUNC, ADDR_MODE, ARGS, CYCLES)         \
        {FUNC, ADDR_MODE, ARGS, CYCLES}

#define OP_TABLE_SIZE   0x100

static opcode_t op_table[OP_TABLE_SIZE] = {
        [LDA_IMM] = OPCODE(op_lda, IMM, 1, 2),
};

opcode_t *
op_get(uint8_t idx)
{
        return &op_table[idx];
}
