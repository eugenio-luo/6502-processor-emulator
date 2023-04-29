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
        reg_force_flags(10);
        cycles = op_exec(PHP, 0, 0);
        TEST_CHECK("php", 1, cycles == 3 && stack_top() == 10);
        cpu_reset(HARD_RESET);

        /* 3. check if 0x68 works */
        stack_push(10);
        cycles = op_exec(PLA, 0, 0);
        TEST_CHECK("pla", 1, cycles == 4 && reg_get_acc() == 10);
        cpu_reset(HARD_RESET);

        /* 4. check if 0x28 works */
        reg_force_flags(0x24);
        stack_push(0x40);
        cycles = op_exec(PLP, 0, 0);
        TEST_CHECK("plp", 1, cycles == 4 && reg_get_flags() == 0x60);
        cpu_reset(HARD_RESET);
}

