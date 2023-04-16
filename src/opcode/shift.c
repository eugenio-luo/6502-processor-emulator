#include "opcode/opfunc.h"
#include "opcode/addr_mode.h"
#include "cpu/registers.h"

static void
op_shift_instr(uint8_t new_val, int carry_cond)
{
        set_affected_flags(new_val);
        reg_clear_flags(CARRY_FLAG);
        if (carry_cond)
                reg_set_flags(CARRY_FLAG);
}

int
op_asl(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b);
        uint8_t new_val = val << 1;

        op_shift_instr(new_val, val & 0x80);
       
        op_set_addr_val(addr_mode, a, b, new_val);
        return 0;
}

int
op_lsr(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b);
        uint8_t new_val = val >> 1;

        op_shift_instr(new_val, val & 0x1);
        
        op_set_addr_val(addr_mode, a, b, new_val);
        return 0;
}

int
op_rol(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b);
        uint8_t new_val = (val << 1) | reg_is_flag_set(CARRY_FLAG);

        op_shift_instr(new_val, val & 0x80);
        
        op_set_addr_val(addr_mode, a, b, new_val);
        return 0;
}

int
op_ror(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b);
        uint8_t new_val = (val >> 1) | (reg_is_flag_set(CARRY_FLAG) << 7);

        op_shift_instr(new_val, val & 0x1);
        
        op_set_addr_val(addr_mode, a, b, new_val);
        return 0;
}
