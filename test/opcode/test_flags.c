#include "test_op.h"
#include "test_check.h"
#include "cpu/cpu.h"
#include "opcode/optable.h"
#include "opcode/opcode.h"
#include "cpu/registers.h"

void
test_op_flags(void)
{
        int cycles;
        
        /* 1. check if 0x18 works */
        reg_set_flags(CARRY_FLAG);
        cycles = op_exec(CLC, 0, 0);
        TEST_CHECK("clc", 1, cycles == 2 && !reg_is_flag_set(CARRY_FLAG)); 
        cpu_reset(HARD_RESET);

        /* 1. check if 0xD8 works */
        reg_set_flags(DEC_MODE);
        cycles = op_exec(CLD, 0, 0);
        TEST_CHECK("cld", 1, cycles == 2 && !reg_is_flag_set(DEC_MODE)); 
        cpu_reset(HARD_RESET);

        /* 1. check if 0x58 works */
        reg_set_flags(INT_DISABLE);
        cycles = op_exec(CLI, 0, 0);
        TEST_CHECK("cli", 1, cycles == 2 && !reg_is_flag_set(INT_DISABLE)); 
        cpu_reset(HARD_RESET);

        /* 1. check if 0xB8 works */
        reg_set_flags(OVER_FLAG);
        cycles = op_exec(CLV, 0, 0);
        TEST_CHECK("clv", 1, cycles == 2 && !reg_is_flag_set(OVER_FLAG)); 
        cpu_reset(HARD_RESET);
}
