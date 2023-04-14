#include "opcode/opfunc.h"
#include "opcode/addr_mode.h"
#include "cpu/registers.h"

int
op_tax(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;

        uint8_t val = reg_get_acc();
        reg_set_x(val);

        set_affected_flags(val);

        return 0;
}

int
op_tay(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;

        uint8_t val = reg_get_acc();
        reg_set_y(val);

        set_affected_flags(val);

        return 0;
}

int
op_tsx(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;

        uint8_t val = reg_get_sp();
        reg_set_x(val);

        set_affected_flags(val);

        return 0;
}

int
op_txa(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;

        uint8_t val = reg_get_x();
        reg_set_acc(val);

        set_affected_flags(val);

        return 0;
}

int
op_txs(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;
        
        uint8_t val = reg_get_x();
        reg_set_sp(val);

        return 0;
}

int
op_tya(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;

        uint8_t val = reg_get_y();
        reg_set_acc(val);

        set_affected_flags(val);

        return 0;
}
