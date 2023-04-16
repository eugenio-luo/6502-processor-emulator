#include "opcode/opfunc.h"
#include "cpu/registers.h"

static void
op_transfer_instr(uint8_t (*get_func)(void), void (*set_func)(uint8_t))
{
        uint8_t val = get_func();
        set_func(val);
        set_affected_flags(val);
}

int
op_tax(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;

        op_transfer_instr(reg_get_acc, reg_set_x);
        return 0;
}

int
op_tay(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;

        op_transfer_instr(reg_get_acc, reg_set_y);
        return 0;
}

int
op_tsx(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;

        op_transfer_instr(reg_get_sp, reg_set_x);
        return 0;
}

int
op_txa(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;

        op_transfer_instr(reg_get_x, reg_set_acc);
        return 0;
}

int
op_txs(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;
        
        op_transfer_instr(reg_get_x, reg_set_sp);
        return 0;
}

int
op_tya(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;

        op_transfer_instr(reg_get_y, reg_set_acc);
        return 0;
}
