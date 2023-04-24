#include "opcode/opfunc.h"
#include "opcode/addr_mode.h"
#include "cpu/registers.h"
#include "cpu/stack.h"
#include "cpu/memory.h"

int
op_brk(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;

        /* TODO: im not sure about in which order they should
                 be pushed on the stack */
        addr_t pc = reg_get_pc() + 2;
        stack_push(pc >> 8);
        stack_push(pc & 0xFF);
        stack_push(reg_get_flags() | BREAK_COM0);

        reg_set_flags(INT_DISABLE);
        reg_set_pc(mem_get(0xFFFF) << 8 | mem_get(0xFFFE));
        
        return 0;
}

int
op_jmp(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        addr_t addr = op_get_addr(addr_mode, a, b);
        reg_set_pc(addr);
        return 0;
}
