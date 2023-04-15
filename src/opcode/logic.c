#include "opcode/opfunc.h"
#include "opcode/addr_mode.h"
#include "cpu/registers.h"

int
op_and(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b);
        uint8_t new_val = val & reg_get_acc();
        reg_set_acc(new_val);

        set_affected_flags(new_val);

        return op_get_page_cross();
}
