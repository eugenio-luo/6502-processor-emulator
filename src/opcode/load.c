#include "opcode/opcode.h"
#include "opcode/opfunc.h"
#include "opcode/optable.h"
#include "opcode/addr_mode.h"
#include "cpu/registers.h"

int
op_lda(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        uint8_t val = op_get_addr_val(addr_mode, a, b);
        reg_set_acc(val);

        reg_clear_flags(ZERO_FLAG | NEG_FLAG);
        if (val == 0)
                reg_set_flags(ZERO_FLAG);
        else if (val & 0x80)
                reg_set_flags(NEG_FLAG);

        return op_get_page_cross();
}
