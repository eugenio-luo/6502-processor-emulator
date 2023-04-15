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
