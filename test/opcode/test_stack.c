#include "test_op.h"
#include "test_check.h"
#include "cpu/cpu.h"
#include "cpu/stack.h"
#include "cpu/registers.h"
#include "opcode/opcode.h"
#include "opcode/optable.h"

void
test_op_stack(void)
{
        int cycles;

        /* 1. check if 0x48 works */
        reg_set_acc(10);
        cycles = op_exec(PHA, 0, 0);
        TEST_CHECK("pha", 1, cycles == 3 && stack_top() == 10);
        cpu_reset(HARD_RESET);

        /* 2. check if 0x08 works */
        reg_clear_flags(0xFF);
        reg_set_flags(10);
        cycles = op_exec(PHP, 0, 0);
        printf("%x\n", stack_top());
        TEST_CHECK("php", 1, cycles == 3 && stack_top() == 10);
        cpu_reset(HARD_RESET);
}
