#ifndef NES_OPFUNC_H
#define NES_OPFUNC_H

#include "opcode/optable.h"

#define OP_FUNC_DECL(NAME) int NAME(addr_mode_t addr_mode, uint8_t a, uint8_t b)

void set_affected_flags(uint8_t val);

OP_FUNC_DECL(op_lda);
OP_FUNC_DECL(op_ldx);
OP_FUNC_DECL(op_ldy);
OP_FUNC_DECL(op_sta);
OP_FUNC_DECL(op_stx);
OP_FUNC_DECL(op_sty);

OP_FUNC_DECL(op_tax);
OP_FUNC_DECL(op_tay);
OP_FUNC_DECL(op_tsx);
OP_FUNC_DECL(op_txa);
OP_FUNC_DECL(op_txs);
OP_FUNC_DECL(op_tya);

OP_FUNC_DECL(op_pha);
OP_FUNC_DECL(op_php);
OP_FUNC_DECL(op_pla);
OP_FUNC_DECL(op_plp);

OP_FUNC_DECL(op_asl);
OP_FUNC_DECL(op_lsr);
OP_FUNC_DECL(op_rol);
OP_FUNC_DECL(op_ror);

OP_FUNC_DECL(op_and);
OP_FUNC_DECL(op_bit);
OP_FUNC_DECL(op_eor);
OP_FUNC_DECL(op_ora);

OP_FUNC_DECL(op_adc);
OP_FUNC_DECL(op_cmp);
OP_FUNC_DECL(op_cpx);
OP_FUNC_DECL(op_cpy);
OP_FUNC_DECL(op_sbc);

OP_FUNC_DECL(op_dec);
OP_FUNC_DECL(op_dex);
OP_FUNC_DECL(op_dey);
OP_FUNC_DECL(op_inc);
OP_FUNC_DECL(op_inx);
OP_FUNC_DECL(op_iny);

OP_FUNC_DECL(op_bcc);
OP_FUNC_DECL(op_bcs);
OP_FUNC_DECL(op_beq);
OP_FUNC_DECL(op_bmi);
OP_FUNC_DECL(op_bne);
OP_FUNC_DECL(op_bpl);
OP_FUNC_DECL(op_bvc);
OP_FUNC_DECL(op_bvs);

OP_FUNC_DECL(op_clc);
OP_FUNC_DECL(op_cld);
OP_FUNC_DECL(op_cli);
OP_FUNC_DECL(op_clv);
OP_FUNC_DECL(op_sec);
OP_FUNC_DECL(op_sed);
OP_FUNC_DECL(op_sei);

OP_FUNC_DECL(op_brk);
OP_FUNC_DECL(op_jmp);
OP_FUNC_DECL(op_jsr);
OP_FUNC_DECL(op_rti);
OP_FUNC_DECL(op_rts);
OP_FUNC_DECL(op_nop);

#endif
