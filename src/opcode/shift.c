#include "opcode/opfunc.h"
#include "opcode/addr_mode.h"
#include "cpu/registers.h"

int
op_asl(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b);
        uint8_t new_val = val << 1;

        set_affected_flags(new_val);
        if (val & 0x80)
                reg_set_flags(CARRY_FLAG);
        
        op_set_addr_val(addr_mode, a, b, new_val);
        return 0;
}

int
op_lsr(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b);
        uint8_t new_val = val >> 1;

        set_affected_flags(new_val);
        if (val & 0x1)
                reg_set_flags(CARRY_FLAG);

        op_set_addr_val(addr_mode, a, b, new_val);
        return 0;
}
