#include "opcode/opfunc.h"
#include "opcode/addr_mode.h"
#include "cpu/registers.h"

static int
op_load_instr(uint8_t val, void (*set_func)(uint8_t))
{
        set_func(val);
        set_affected_flags(val);

        return op_get_page_cross();
}

int
op_lda(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b);
        return op_load_instr(val, reg_set_acc);
}

int
op_ldx(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b);
        return op_load_instr(val, reg_set_x);
}

int
op_ldy(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b);
        return op_load_instr(val, reg_set_y);
}

int
op_sta(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = reg_get_acc();
        op_set_addr_val(addr_mode, a, b, val);

        return 0;
}

int
op_stx(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = reg_get_x();
        op_set_addr_val(addr_mode, a, b, val);

        return 0;
}

int
op_sty(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = reg_get_y();
        op_set_addr_val(addr_mode, a, b, val);

        return 0;
}
