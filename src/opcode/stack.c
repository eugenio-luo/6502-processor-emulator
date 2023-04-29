#include "opcode/opfunc.h"
#include "opcode/addr_mode.h"
#include "cpu/registers.h"
#include "cpu/stack.h"

int
op_pha(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;
        
        stack_push(reg_get_acc());

        return 0;
}

int
op_php(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;

        stack_push(reg_get_flags());

        return 0;
}

int
op_pla(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;

        uint8_t val = stack_top();
        stack_pop();
        reg_set_acc(val);

        set_affected_flags(val);
        
        return 0;
}

int
op_plp(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;

        /* TODO: should BREAK flag be changed? */
        uint8_t new_flag = stack_top();
        stack_pop();
        uint8_t actual_flag = reg_get_flags();
        new_flag &= ~(BREAK_COM0 | BREAK_COM1);
        new_flag |= actual_flag & (BREAK_COM0 | BREAK_COM1);
        reg_force_flags(new_flag);

        return 0;
}
