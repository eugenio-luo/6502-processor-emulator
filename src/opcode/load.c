#include "opcode/opfunc.h"
#include "opcode/addr_mode.h"
#include "cpu/registers.h"

static void
set_affected_flags(uint8_t val)
{
        reg_clear_flags(ZERO_FLAG | NEG_FLAG);
        if (val == 0)
                reg_set_flags(ZERO_FLAG);
        else if (val & 0x80)
                reg_set_flags(NEG_FLAG);
}

int
op_lda(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b);
        reg_set_acc(val);

        set_affected_flags(val);
        
        return op_get_page_cross();
}

int
op_ldx(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b);
        reg_set_x(val);

        set_affected_flags(val);

        return op_get_page_cross();
}

int
op_ldy(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b);
        reg_set_y(val);

        set_affected_flags(val);

        return op_get_page_cross();
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
