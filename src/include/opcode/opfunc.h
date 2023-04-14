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

#endif
