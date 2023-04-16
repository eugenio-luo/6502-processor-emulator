#include "opcode/opfunc.h"
#include "opcode/addr_mode.h"
#include "cpu/registers.h"

#include "log.h"

static int
op_addition_instr(uint8_t val)
{
        uint8_t acc = reg_get_acc();
        int new_val = val + acc + reg_is_flag_set(CARRY_FLAG);
        uint8_t new_byte = new_val & 0xFF;
        log_write("second operand: %x, %x, %x, %x", val, acc, new_val, new_byte);
        reg_set_acc(new_byte);
        
        set_affected_flags(new_byte);
        reg_clear_flags(CARRY_FLAG | OVER_FLAG);
        if (new_val > 0xFF)
                reg_set_flags(CARRY_FLAG);
        if (~(val ^ acc) & (val ^ new_val) & 0x80)
                reg_set_flags(OVER_FLAG);

        return op_get_page_cross();
}

int
op_adc(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b);
        return op_addition_instr(val);
}

int
op_sbc(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b);
        return op_addition_instr(~val);
}

static int 
op_compare_instr(uint8_t val, uint8_t reg)
{
        uint8_t new_val = reg - val;

        set_affected_flags(new_val);
        reg_clear_flags(CARRY_FLAG);
        if (reg >= val)
                reg_set_flags(CARRY_FLAG);

        return op_get_page_cross();
}

int
op_cmp(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b);
        return op_compare_instr(val, reg_get_acc());
}

int
op_cpx(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b);
        return op_compare_instr(val, reg_get_x());
}

int
op_cpy(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b);
        return op_compare_instr(val, reg_get_y());
}

