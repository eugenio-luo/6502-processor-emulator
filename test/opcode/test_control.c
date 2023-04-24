#include "test_op.h"
#include "test_check.h"
#include "cpu/cpu.h"
#include "opcode/optable.h"
#include "opcode/opcode.h"
#include "cpu/registers.h"
#include "cpu/memory.h"
#include "cpu/stack.h"

static void
test_brk(void)
{
        int cycles;

        /* 1. check if 0x00 works */
        uint8_t old_flags = reg_get_flags();
        mem_set(0xFFFE, 0x32);
        mem_set(0xFFFF, 0x4);
        reg_set_pc(0x100);
        cycles = op_exec(BRK, 0, 0);
        uint8_t flags = stack_top();
        stack_pop();
        uint8_t pcl = stack_top();
        stack_pop();
        uint8_t pch = stack_top();
        TEST_CHECK("brk", 1, cycles == 7 && reg_get_pc() == 0x432 &&
                   reg_is_flag_set(INT_DISABLE) &&
                   flags == (old_flags | BREAK_COM0) &&
                   pcl == 0x2 && pch == 0x1);
        cpu_reset(HARD_RESET);
}

void
test_op_control(void)
{
        test_brk();
}
