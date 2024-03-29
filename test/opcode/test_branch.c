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

static void
test_bcs(void)
{
        int cycles;

        /* 1. check if 0xB0 works if CARRY_FLAG is set */
        reg_set_flags(CARRY_FLAG);
        reg_set_pc(0x100);
        cycles = op_exec(BCS, 0x10, 0);
        TEST_CHECK("bcs", 1, cycles == 3 && reg_get_pc() == 0x110);
        cpu_reset(HARD_RESET);

        /* 2. check if 0xB0 fails if CARRY_FLAG is clear */
        reg_clear_flags(CARRY_FLAG);
        reg_set_pc(0x100);
        cycles = op_exec(BCS, 0x10, 0);
        TEST_CHECK("bcs", 2, cycles == 2 && reg_get_pc() == 0x100);
        cpu_reset(HARD_RESET);

        /* 3. check if 0xB0 cycles increases if page boundary is crossed */
        reg_set_flags(CARRY_FLAG);
        reg_set_pc(0xFF);
        cycles = op_exec(BCS, 0x2, 0);
        TEST_CHECK("bcs", 3, cycles == 4 && reg_get_pc() == 0x101);
        cpu_reset(HARD_RESET);
}

static void
test_beq(void)
{
        int cycles;

        /* 1. check if 0xF0 works if ZERO_FLAG is set */
        reg_set_flags(ZERO_FLAG);
        reg_set_pc(0x100);
        cycles = op_exec(BEQ, 0x10, 0);
        TEST_CHECK("beq", 1, cycles == 3 && reg_get_pc() == 0x110);
        cpu_reset(HARD_RESET);

        /* 2. check if 0xF0 fails if ZERO_FLAG is clear */
        reg_clear_flags(ZERO_FLAG);
        reg_set_pc(0x100);
        cycles = op_exec(BEQ, 0x10, 0);
        TEST_CHECK("beq", 2, cycles == 2 && reg_get_pc() == 0x100);
        cpu_reset(HARD_RESET);

        /* 3. check if 0xF0 cycles increases if page boundary is crossed */
        reg_set_flags(ZERO_FLAG);
        reg_set_pc(0xFF);
        cycles = op_exec(BEQ, 0x2, 0);
        TEST_CHECK("beq", 3, cycles == 4 && reg_get_pc() == 0x101);
        cpu_reset(HARD_RESET);
}

static void
test_bmi(void)
{
        int cycles;

        /* 1. check if 0x30 works if NEG_FLAG is set */
        reg_set_flags(NEG_FLAG);
        reg_set_pc(0x100);
        cycles = op_exec(BMI, 0x10, 0);
        TEST_CHECK("bmi", 1, cycles == 3 && reg_get_pc() == 0x110);
        cpu_reset(HARD_RESET);

        /* 2. check if 0x30 fails if NEG_FLAG is clear */
        reg_clear_flags(NEG_FLAG);
        reg_set_pc(0x100);
        cycles = op_exec(BMI, 0x10, 0);
        TEST_CHECK("bmi", 2, cycles == 2 && reg_get_pc() == 0x100);
        cpu_reset(HARD_RESET);

        /* 3. check if 0x30 cycles increases if page boundary is crossed */
        reg_set_flags(NEG_FLAG);
        reg_set_pc(0xFF);
        cycles = op_exec(BMI, 0x2, 0);
        TEST_CHECK("bmi", 3, cycles == 4 && reg_get_pc() == 0x101);
        cpu_reset(HARD_RESET);
}

static void
test_bne(void)
{
        int cycles;

        /* 1. check if 0xD0 works if ZERO_FLAG is clear */
        reg_clear_flags(ZERO_FLAG);
        reg_set_pc(0x100);
        cycles = op_exec(BNE, 0x10, 0);
        TEST_CHECK("bne", 1, cycles == 3 && reg_get_pc() == 0x110);
        cpu_reset(HARD_RESET);

        /* 2. check if 0xD0 fails if ZERO_FLAG is set */
        reg_set_flags(ZERO_FLAG);
        reg_set_pc(0x100);
        cycles = op_exec(BNE, 0x10, 0);
        TEST_CHECK("bne", 2, cycles == 2 && reg_get_pc() == 0x100);
        cpu_reset(HARD_RESET);

        /* 3. check if 0xD0 cycles increases if page boundary is crossed */
        reg_clear_flags(ZERO_FLAG);
        reg_set_pc(0xFF);
        cycles = op_exec(BNE, 0x2, 0);
        TEST_CHECK("bne", 3, cycles == 4 && reg_get_pc() == 0x101);
        cpu_reset(HARD_RESET);
}

static void
test_bpl(void)
{
        int cycles;

        /* 1. check if 0x10 works if NEG_FLAG is clear */
        reg_clear_flags(NEG_FLAG);
        reg_set_pc(0x100);
        cycles = op_exec(BPL, 0x10, 0);
        TEST_CHECK("bpl", 1, cycles == 3 && reg_get_pc() == 0x110);
        cpu_reset(HARD_RESET);

        /* 2. check if 0x10 fails if NEG_FLAG is set */
        reg_set_flags(NEG_FLAG);
        reg_set_pc(0x100);
        cycles = op_exec(BPL, 0x10, 0);
        TEST_CHECK("bpl", 2, cycles == 2 && reg_get_pc() == 0x100);
        cpu_reset(HARD_RESET);

        /* 3. check if 0x10 cycles increases if page boundary is crossed */
        reg_clear_flags(NEG_FLAG);
        reg_set_pc(0xFF);
        cycles = op_exec(BPL, 0x2, 0);
        TEST_CHECK("bpl", 3, cycles == 4 && reg_get_pc() == 0x101);
        cpu_reset(HARD_RESET);
}

static void
test_bvc(void)
{
        int cycles;

        /* 1. check if 0x50 works if OVER_FLAG is clear */
        reg_clear_flags(OVER_FLAG);
        reg_set_pc(0x100);
        cycles = op_exec(BVC, 0x10, 0);
        TEST_CHECK("bvc", 1, cycles == 3 && reg_get_pc() == 0x110);
        cpu_reset(HARD_RESET);

        /* 2. check if 0x50 fails if OVER_FLAG is set */
        reg_set_flags(OVER_FLAG);
        reg_set_pc(0x100);
        cycles = op_exec(BVC, 0x10, 0);
        TEST_CHECK("bvc", 2, cycles == 2 && reg_get_pc() == 0x100);
        cpu_reset(HARD_RESET);

        /* 3. check if 0x50 cycles increases if page boundary is crossed */
        reg_clear_flags(OVER_FLAG);
        reg_set_pc(0xFF);
        cycles = op_exec(BVC, 0x2, 0);
        TEST_CHECK("bvc", 3, cycles == 4 && reg_get_pc() == 0x101);
        cpu_reset(HARD_RESET);
}

static void
test_bvs(void)
{
        int cycles;

        /* 1. check if 0x70 works if OVER_FLAG is set */
        reg_set_flags(OVER_FLAG);
        reg_set_pc(0x100);
        cycles = op_exec(BVS, 0x10, 0);
        TEST_CHECK("bvs", 1, cycles == 3 && reg_get_pc() == 0x110);
        cpu_reset(HARD_RESET);

        /* 2. check if 0x70 fails if OVER_FLAG is clear */
        reg_clear_flags(OVER_FLAG);
        reg_set_pc(0x100);
        cycles = op_exec(BVS, 0x10, 0);
        TEST_CHECK("bvs", 2, cycles == 2 && reg_get_pc() == 0x100);
        cpu_reset(HARD_RESET);

        /* 3. check if 0x70 cycles increases if page boundary is crossed */
        reg_set_flags(OVER_FLAG);
        reg_set_pc(0xFF);
        cycles = op_exec(BVS, 0x2, 0);
        TEST_CHECK("bvs", 3, cycles == 4 && reg_get_pc() == 0x101);
        cpu_reset(HARD_RESET);
}

void
test_op_branch(void)
{
        test_bcc();
        test_bcs();
        test_beq();
        test_bmi();
        test_bne();
        test_bpl();
        test_bvc();
        test_bvs();
}
