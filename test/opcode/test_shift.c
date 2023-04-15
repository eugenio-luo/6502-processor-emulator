#include "test_op.h"
#include "test_check.h"
#include "cpu/cpu.h"
#include "opcode/optable.h"
#include "opcode/opcode.h"
#include "cpu/registers.h"
#include "cpu/memory.h"

static void
test_asl(void)
{
        int cycles;

        /* 1. check if 0x0A works, NEG_FLAG, ZERO_FLAG and CARRY FLAG 
              shouldn't be set */
        reg_set_acc(8);
        cycles = op_exec(ASL_ACC, 0, 0);
        TEST_CHECK("asl", 1, cycles == 2 && reg_get_acc() == 16 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG | CARRY_FLAG) ));
        cpu_reset(HARD_RESET);
        
        /* 2. check if ZERO_FLAG and CARRY_FLAG get set with 0x80 as 
              0x0A argument */
        reg_set_acc(0x80);
        cycles = op_exec(ASL_ACC, 0, 0);
        TEST_CHECK("asl", 2, cycles == 2 && reg_get_acc() == 0 &&
                   reg_is_flag_set(ZERO_FLAG | CARRY_FLAG));
        cpu_reset(HARD_RESET);

        /* 3. check if NEG_FLAG get set with 0x40 as 0x0A argument */
        reg_set_acc(0x40);
        cycles = op_exec(ASL_ACC, 0, 0);
        TEST_CHECK("asl", 3, cycles == 2 && reg_get_acc() == 0x80 &&
                   reg_is_flag_set(NEG_FLAG));
        cpu_reset(HARD_RESET);
        
        /* 4. check if 0x0E works, NEG_FLAG, ZERO_FLAG and CARRY FLAG 
              shouldn't be set */
        mem_set(0x432, 8);
        cycles = op_exec(ASL_ABS, 0x32, 0x4);
        TEST_CHECK("asl", 4, cycles == 6 && mem_get(0x432) == 16 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG | CARRY_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 5. check if 0x1E works, NEG_FLAG, ZERO_FLAG and CARRY FLAG 
              shouldn't be set */
        mem_set(0x432, 8);
        reg_set_x(0x10);
        cycles = op_exec(ASL_ABSX, 0x22, 0x4);
        TEST_CHECK("asl", 5, cycles == 7 && mem_get(0x432) == 16 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG | CARRY_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 6. check if 0x06 works, NEG_FLAG, ZERO_FLAG and CARRY FLAG 
              shouldn't be set */
        mem_set(0x32, 8);
        cycles = op_exec(ASL_ZERO, 0x32, 0);
        TEST_CHECK("asl", 6, cycles == 5 && mem_get(0x32) == 16 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG | CARRY_FLAG) ));
        cpu_reset(HARD_RESET);
        
        /* 7. check if 0x16 works, NEG_FLAG, ZERO_FLAG and CARRY FLAG 
              shouldn't be set */
        mem_set(0x32, 8);
        reg_set_x(0x10);
        cycles = op_exec(ASL_ZEROX, 0x22, 0);
        TEST_CHECK("asl", 7, cycles == 6 && mem_get(0x32) == 16 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG | CARRY_FLAG) ));
        cpu_reset(HARD_RESET);
}

static void
test_lsr(void)
{
        int cycles;

        /* 1. check if 0x4A works, NEG_FLAG, ZERO_FLAG and CARRY FLAG 
              shouldn't be set */
        reg_set_acc(8);
        cycles = op_exec(LSR_ACC, 0, 0);
        TEST_CHECK("lsr", 1, cycles == 2 && reg_get_acc() == 4 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG | CARRY_FLAG) ));
        cpu_reset(HARD_RESET);
        
        /* 2. check if ZERO_FLAG and CARRY_FLAG get set with 0x1 as 
              0x4A argument */
        reg_set_acc(0x1);
        cycles = op_exec(LSR_ACC, 0, 0);
        TEST_CHECK("lsr", 2, cycles == 2 && reg_get_acc() == 0 &&
                   reg_is_flag_set(ZERO_FLAG | CARRY_FLAG));
        cpu_reset(HARD_RESET);

        /* 3. check if 0x4E works, NEG_FLAG, ZERO_FLAG and CARRY FLAG 
              shouldn't be set */
        mem_set(0x432, 8);
        cycles = op_exec(LSR_ABS, 0x32, 0x4);
        TEST_CHECK("lsr", 3, cycles == 6 && mem_get(0x432) == 4 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG | CARRY_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 4. check if 0x5E works, NEG_FLAG, ZERO_FLAG and CARRY FLAG 
              shouldn't be set */
        mem_set(0x432, 8);
        reg_set_x(0x10);
        cycles = op_exec(LSR_ABSX, 0x22, 0x4);
        TEST_CHECK("lsr", 4, cycles == 7 && mem_get(0x432) == 4 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG | CARRY_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 5. check if 0x46 works, NEG_FLAG, ZERO_FLAG and CARRY FLAG 
              shouldn't be set */
        mem_set(0x32, 8);
        cycles = op_exec(LSR_ZERO, 0x32, 0);
        TEST_CHECK("lsr", 5, cycles == 5 && mem_get(0x32) == 4 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG | CARRY_FLAG) ));
        cpu_reset(HARD_RESET);
        
        /* 6. check if 0x56 works, NEG_FLAG, ZERO_FLAG and CARRY FLAG 
              shouldn't be set */
        mem_set(0x32, 8);
        reg_set_x(0x10);
        cycles = op_exec(LSR_ZEROX, 0x22, 0);
        TEST_CHECK("lsr", 6, cycles == 6 && mem_get(0x32) == 4 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG | CARRY_FLAG) ));
        cpu_reset(HARD_RESET);
}

void
test_op_shift(void)
{
        test_asl();
        test_lsr();
}
