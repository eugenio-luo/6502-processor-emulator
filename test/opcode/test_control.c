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

static void
test_jmp(void)
{
        int cycles;

        /* 1. check if 0x4C works */
        cycles = op_exec(JMP_ABS, 0x32, 0x4);
        TEST_CHECK("jmp", 1, cycles == 3 && reg_get_pc() == 0x432);
        cpu_reset(HARD_RESET);

        /* 1. check if 0x6C works */
        mem_set(0x432, 0x2);
        mem_set(0x433, 0x4);
        cycles = op_exec(JMP_INDR, 0x32, 0x4);
        TEST_CHECK("jmp", 2, cycles == 5 && reg_get_pc() == 0x402);
        cpu_reset(HARD_RESET);
}

static void
test_jsr(void)
{
        int cycles;

        /* 1. check if 0x20 works */
        reg_set_pc(0x104);
        cycles = op_exec(JSR, 0x32, 0x4);
        uint8_t pcl = stack_top();
        stack_pop();
        uint8_t pch = stack_top();
        TEST_CHECK("jsr", 1, cycles == 6 && reg_get_pc() == 0x432 &&
                   pcl == 0x4 && pch == 0x1);
        cpu_reset(HARD_RESET);
}

static void
test_rti(void)
{
        int cycles;

        /* check if 0x40 works */
        uint8_t old_flags = reg_get_flags();
        reg_set_pc(0x100);
        op_exec(BRK, 0, 0);
        cycles = op_exec(RTI, 0, 0);
        TEST_CHECK("rti", 1, cycles == 6 && reg_get_pc() == 0x102 &&
                   reg_get_flags() == old_flags);
        cpu_reset(HARD_RESET);
}

void
test_op_control(void)
{
        test_brk();
        test_jmp();
        test_jsr();
        test_rti();
}
