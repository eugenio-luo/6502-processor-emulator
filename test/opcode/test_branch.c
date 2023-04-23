#include "test_op.h"
#include "test_check.h"
#include "cpu/cpu.h"
#include "opcode/optable.h"
#include "opcode/opcode.h"
#include "cpu/registers.h"

static void
test_bcc(void)
{
        int cycles;

        /* 1. check if 0x90 works if CARRY_FLAG is clear */
        reg_clear_flags(CARRY_FLAG);
        reg_set_pc(0x100);
        cycles = op_exec(BCC, 0x10, 0);
        TEST_CHECK("bcc", 1, cycles == 3 && reg_get_pc() == 0x110);
        cpu_reset(HARD_RESET);

        /* 2. check if 0x90 fails if CARRY_FLAG is set */
        reg_set_flags(CARRY_FLAG);
        reg_set_pc(0x100);
        cycles = op_exec(BCC, 0x10, 0);
        TEST_CHECK("bcc", 2, cycles == 2 && reg_get_pc() == 0x100);
        cpu_reset(HARD_RESET);

        /* 3. check if 0x90 cycles increases if page boundary is crossed */
        reg_clear_flags(CARRY_FLAG);
        reg_set_pc(0xFF);
        cycles = op_exec(BCC, 0x2, 0);
        TEST_CHECK("bcc", 3, cycles == 4 && reg_get_pc() == 0x101);
        cpu_reset(HARD_RESET);
}

void
test_op_branch(void)
{
        test_bcc();
}
