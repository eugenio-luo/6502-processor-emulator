#include "test_op.h"
#include "test_check.h"
#include "cpu/cpu.h"
#include "cpu/registers.h"
#include "opcode/opcode.h"
#include "opcode/optable.h"

void
test_transfer(void)
{
        int cycles;
        
        /* 1. check if 0xAA works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_acc(10);
        cycles = op_exec(TAX, 0, 0);
        TEST_CHECK("tax", 1, cycles == 2 && reg_get_x() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 2. check if ZERO_FLAG get set with zero as 0xAA argument */
        cycles = op_exec(TAX, 0, 0);
        TEST_CHECK("tax", 2, cycles == 2 && reg_get_x() == 0 &&
                   reg_is_flag_set(ZERO_FLAG));
        cpu_reset(HARD_RESET);

        /* 3. check if NEG_FLAG get set with negative number as 0xAA argument */
        reg_set_acc(-1);
        cycles = op_exec(TAX, 0, 0);
        TEST_CHECK("tax", 3, cycles == 2 && reg_get_x() == 0xFF &&
                   reg_is_flag_set(NEG_FLAG));
        cpu_reset(HARD_RESET);

        /* 1. check if 0xAA works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_acc(10);
        cycles = op_exec(TAY, 0, 0);
        TEST_CHECK("tay", 1, cycles == 2 && reg_get_y() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);
}

