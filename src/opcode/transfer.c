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
