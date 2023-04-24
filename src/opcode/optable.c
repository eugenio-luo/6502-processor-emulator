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

        [ROR_ACC] = OPCODE(op_ror, ACC, 0, 2),
        [ROR_ABS] = OPCODE(op_ror, ABS, 2, 6),
        [ROR_ABSX] = OPCODE(op_ror, ABSX, 2, 7),
        [ROR_ZERO] = OPCODE(op_ror, ZERO, 1, 5),
        [ROR_ZEROX] = OPCODE(op_ror, ZEROX, 1, 6),

        [AND_IMM] = OPCODE(op_and, IMM, 1, 2),
        [AND_ABS] = OPCODE(op_and, ABS, 2, 4),
        [AND_ABSX] = OPCODE(op_and, ABSX, 2, 4),
        [AND_ABSY] = OPCODE(op_and, ABSY, 2, 4),
        [AND_ZERO] = OPCODE(op_and, ZERO, 1, 3),
        [AND_ZEROX] = OPCODE(op_and, ZEROX, 1, 4),
        [AND_INDX_INDR] = OPCODE(op_and, INDX_INDR, 1, 6),
        [AND_INDR_INDY] = OPCODE(op_and, INDR_INDY, 1, 5),

        [BIT_ABS] = OPCODE(op_bit, ABS, 2, 4),
        [BIT_ZERO] = OPCODE(op_bit, ZERO, 1, 3),

        [EOR_IMM] = OPCODE(op_eor, IMM, 1, 2),
        [EOR_ABS] = OPCODE(op_eor, ABS, 2, 4),
        [EOR_ABSX] = OPCODE(op_eor, ABSX, 2, 4),
        [EOR_ABSY] = OPCODE(op_eor, ABSY, 2, 4),
        [EOR_ZERO] = OPCODE(op_eor, ZERO, 1, 3),
        [EOR_ZEROX] = OPCODE(op_eor, ZEROX, 1, 4),
        [EOR_INDX_INDR] = OPCODE(op_eor, INDX_INDR, 1, 6),
        [EOR_INDR_INDY] = OPCODE(op_eor, INDR_INDY, 1, 5),

        [ORA_IMM] = OPCODE(op_ora, IMM, 1, 2),
        [ORA_ABS] = OPCODE(op_ora, ABS, 2, 4),
        [ORA_ABSX] = OPCODE(op_ora, ABSX, 2, 4),
        [ORA_ABSY] = OPCODE(op_ora, ABSY, 2, 4),
        [ORA_ZERO] = OPCODE(op_ora, ZERO, 1, 3),
        [ORA_ZEROX] = OPCODE(op_ora, ZEROX, 1, 4),
        [ORA_INDX_INDR] = OPCODE(op_ora, INDX_INDR, 1, 6),
        [ORA_INDR_INDY] = OPCODE(op_ora, INDR_INDY, 1, 5),

        [ADC_IMM] = OPCODE(op_adc, IMM, 1, 2),
        [ADC_ABS] = OPCODE(op_adc, ABS, 2, 4),
        [ADC_ABSX] = OPCODE(op_adc, ABSX, 2, 4),
        [ADC_ABSY] = OPCODE(op_adc, ABSY, 2, 4),
        [ADC_ZERO] = OPCODE(op_adc, ZERO, 1, 3),
        [ADC_ZEROX] = OPCODE(op_adc, ZEROX, 1, 4),
        [ADC_INDX_INDR] = OPCODE(op_adc, INDX_INDR, 1, 6),
        [ADC_INDR_INDY] = OPCODE(op_adc, INDR_INDY, 1, 5),

        [CMP_IMM] = OPCODE(op_cmp, IMM, 1, 2),
        [CMP_ABS] = OPCODE(op_cmp, ABS, 2, 4),
        [CMP_ABSX] = OPCODE(op_cmp, ABSX, 2, 4),
        [CMP_ABSY] = OPCODE(op_cmp, ABSY, 2, 4),
        [CMP_ZERO] = OPCODE(op_cmp, ZERO, 1, 3),
        [CMP_ZEROX] = OPCODE(op_cmp, ZEROX, 1, 4),
        [CMP_INDX_INDR] = OPCODE(op_cmp, INDX_INDR, 1, 6),
        [CMP_INDR_INDY] = OPCODE(op_cmp, INDR_INDY, 1, 5),

        [CPX_IMM] = OPCODE(op_cpx, IMM, 1, 2),
        [CPX_ABS] = OPCODE(op_cpx, ABS, 2, 4),
        [CPX_ZERO] = OPCODE(op_cpx, ZERO, 1, 3),

        [CPY_IMM] = OPCODE(op_cpy, IMM, 1, 2),
        [CPY_ABS] = OPCODE(op_cpy, ABS, 2, 4),
        [CPY_ZERO] = OPCODE(op_cpy, ZERO, 1, 3),

        [SBC_IMM] = OPCODE(op_sbc, IMM, 1, 2),
        [SBC_ABS] = OPCODE(op_sbc, ABS, 2, 4),
        [SBC_ABSX] = OPCODE(op_sbc, ABSX, 2, 4),
        [SBC_ABSY] = OPCODE(op_sbc, ABSY, 2, 4),
        [SBC_ZERO] = OPCODE(op_sbc, ZERO, 1, 3),
        [SBC_ZEROX] = OPCODE(op_sbc, ZEROX, 1, 4),
        [SBC_INDX_INDR] = OPCODE(op_sbc, INDX_INDR, 1, 6),
        [SBC_INDR_INDY] = OPCODE(op_sbc, INDR_INDY, 1, 5),

        [DEC_ABS] = OPCODE(op_dec, ABS, 2, 6),
        [DEC_ABSX] = OPCODE(op_dec, ABSX, 2, 7),
        [DEC_ZERO] = OPCODE(op_dec, ZERO, 1, 5),
        [DEC_ZEROX] = OPCODE(op_dec, ZEROX, 1, 6),

        [DEX] = OPCODE(op_dex, IMPL, 0, 2),
        [DEY] = OPCODE(op_dey, IMPL, 0, 2),

        [INC_ABS] = OPCODE(op_inc, ABS, 2, 6),
        [INC_ABSX] = OPCODE(op_inc, ABSX, 2, 7),
        [INC_ZERO] = OPCODE(op_inc, ZERO, 1, 5),
        [INC_ZEROX] = OPCODE(op_inc, ZEROX, 1, 6),

        [INX] = OPCODE(op_inx, IMPL, 0, 2),
        [INY] = OPCODE(op_iny, IMPL, 0, 2),

        [BCC] = OPCODE(op_bcc, REL, 1, 2),
        [BCS] = OPCODE(op_bcs, REL, 1, 2),
        [BEQ] = OPCODE(op_beq, REL, 1, 2),
        [BMI] = OPCODE(op_bmi, REL, 1, 2),
        [BNE] = OPCODE(op_bne, REL, 1, 2),
        [BPL] = OPCODE(op_bpl, REL, 1, 2),
        [BVC] = OPCODE(op_bvc, REL, 1, 2),
        [BVS] = OPCODE(op_bvs, REL, 1, 2),

        [CLC] = OPCODE(op_clc, IMPL, 0, 2),
        [CLD] = OPCODE(op_cld, IMPL, 0, 2),
        [CLI] = OPCODE(op_cli, IMPL, 0, 2),
        [CLV] = OPCODE(op_clv, IMPL, 0, 2),
        [SEC] = OPCODE(op_sec, IMPL, 0, 2),
        [SED] = OPCODE(op_sed, IMPL, 0, 2),
        [SEI] = OPCODE(op_sei, IMPL, 0, 2),

        [BRK] = OPCODE(op_brk, IMPL, 0, 7),
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
