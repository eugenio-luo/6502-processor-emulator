#include "opcode/opfunc.h"
#include "opcode/addr_mode.h"
#include "cpu/registers.h"

static int
op_logic_instr(uint8_t new_val)
{
        reg_set_acc(new_val);
        set_affected_flags(new_val);

        return op_get_page_cross();       
}

int
op_and(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b);
        return op_logic_instr(val & reg_get_acc());
}

int
op_eor(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b);
        return op_logic_instr(val ^ reg_get_acc());
}

int
op_ora(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b);
        return op_logic_instr(val | reg_get_acc());
}

int
op_bit(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b);
        uint8_t new_val = val & reg_get_acc();

        reg_clear_flags(NEG_FLAG | OVER_FLAG | ZERO_FLAG);
        if (val & 0x80)
                reg_set_flags(NEG_FLAG);
        if (val & 0x40)
                reg_set_flags(OVER_FLAG);
        if (!new_val)
                reg_set_flags(ZERO_FLAG);
        
        return 0;
}
