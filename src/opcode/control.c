#include "opcode/opfunc.h"
#include "opcode/addr_mode.h"
#include "cpu/registers.h"
#include "cpu/stack.h"
#include "cpu/memory.h"

static inline void
op_push_pc(uint16_t pc)
{
        stack_push(pc >> 8);
        stack_push(pc & 0xFF);
}

static inline uint16_t
op_pop_pc(void)
{
        uint8_t pcl = stack_top();
        stack_pop();
        uint8_t pch = stack_top();
        stack_pop();
        return (pch << 8) | pcl;
}

int
op_brk(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;

        /* TODO: im not sure about in which order they should
                 be pushed on the stack */
        op_push_pc(reg_get_pc() + 2);
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

int
op_jsr(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        addr_t addr = op_get_addr(addr_mode, a, b);
        op_push_pc(reg_get_pc() + 2);
        reg_set_pc(addr);
        return 0;
}

int
op_rti(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;
        
        reg_force_flags(stack_top());
        stack_pop();
        reg_set_pc(op_pop_pc());
        return 0;
}

int
op_rts(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;

        reg_set_pc(op_pop_pc() + 1);
        return 0;
}

int
op_nop(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;
        return 0;
}
