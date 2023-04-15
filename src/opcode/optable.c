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
        [TAY] = OPCODE(op_tay, IMPL, 0, 2),
        [TSX] = OPCODE(op_tsx, IMPL, 0, 2),
        [TXA] = OPCODE(op_txa, IMPL, 0, 2),
        [TXS] = OPCODE(op_txs, IMPL, 0, 2),
        [TYA] = OPCODE(op_tya, IMPL, 0, 2),

        [PHA] = OPCODE(op_pha, IMPL, 0, 3),
        [PHP] = OPCODE(op_php, IMPL, 0, 3),
        [PLA] = OPCODE(op_pla, IMPL, 0, 4),
        [PLP] = OPCODE(op_plp, IMPL, 0, 4),

        [ASL_ACC] = OPCODE(op_asl, ACC, 0, 2),
        [ASL_ABS] = OPCODE(op_asl, ABS, 2, 6),
        [ASL_ABSX] = OPCODE(op_asl, ABSX, 2, 7),
        [ASL_ZERO] = OPCODE(op_asl, ZERO, 1, 5),
        [ASL_ZEROX] = OPCODE(op_asl, ZEROX, 1, 6),

        [LSR_ACC] = OPCODE(op_lsr, ACC, 0, 2),
        [LSR_ABS] = OPCODE(op_lsr, ABS, 2, 6),
        [LSR_ABSX] = OPCODE(op_lsr, ABSX, 2, 7),
        [LSR_ZERO] = OPCODE(op_lsr, ZERO, 1, 5),
        [LSR_ZEROX] = OPCODE(op_lsr, ZEROX, 1, 6),

        [ROL_ACC] = OPCODE(op_rol, ACC, 0, 2),
        [ROL_ABS] = OPCODE(op_rol, ABS, 2, 6),
        [ROL_ABSX] = OPCODE(op_rol, ABSX, 2, 7),
        [ROL_ZERO] = OPCODE(op_rol, ZERO, 1, 5),
        [ROL_ZEROX] = OPCODE(op_rol, ZEROX, 1, 6),
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
