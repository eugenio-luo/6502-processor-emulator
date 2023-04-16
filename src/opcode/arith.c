#include "opcode/opfunc.h"
#include "opcode/addr_mode.h"
#include "cpu/registers.h"

int
op_adc(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b);
        int new_val = val + reg_get_acc() + reg_is_flag_set(CARRY_FLAG);
        uint8_t new_byte = new_val & 0xFF;
        reg_set_acc(new_byte);
        
        set_affected_flags(new_byte);
        reg_clear_flags(CARRY_FLAG | OVER_FLAG);
        if (new_val > 0xFF)
                reg_set_flags(CARRY_FLAG);
        if ((val ^ new_val) & 0x80)
                reg_set_flags(OVER_FLAG);

        return op_get_page_cross();
}

int
op_cmp(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b);
        uint8_t new_val = reg_get_acc() - val;

        set_affected_flags(new_val);
        reg_clear_flags(CARRY_FLAG);
        if (reg_get_acc() >= val)
                reg_set_flags(CARRY_FLAG);

        return op_get_page_cross();
}
