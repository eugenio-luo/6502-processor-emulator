#include "opcode/opfunc.h"
#include "opcode/addr_mode.h"
#include "cpu/registers.h"

int
op_dec(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b) - 1;
        op_set_addr_val(addr_mode, a, b, val);
        
        set_affected_flags(val);

        return 0;
}

int
op_dex(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;
        
        reg_dec_x();
        set_affected_flags(reg_get_x());
        
        return 0;
}

int
op_dey(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;
        
        reg_dec_y();
        set_affected_flags(reg_get_y());
        
        return 0;
}

int
op_inc(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b) + 1;
        op_set_addr_val(addr_mode, a, b, val);
        
        set_affected_flags(val);

        return 0;
}
