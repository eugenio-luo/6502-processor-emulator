#include "test_op.h"
#include "test_check.h"
#include "cpu/cpu.h"
#include "cpu/registers.h"
#include "opcode/opcode.h"
#include "opcode/optable.h"

void
test_op_transfer(void)
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

        /* 1. check if 0xBA works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_sp(10);
        cycles = op_exec(TSX, 0, 0);
        TEST_CHECK("tsx", 1, cycles == 2 && reg_get_x() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 1. check if 0x8A works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_x(10);
        cycles = op_exec(TXA, 0, 0);
        TEST_CHECK("txa", 1, cycles == 2 && reg_get_acc() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 1. check if 0x9A works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_x(10);
        cycles = op_exec(TXS, 0, 0);
        TEST_CHECK("txs", 1, cycles == 2 && reg_get_sp() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 1. check if 0x98 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_y(10);
        cycles = op_exec(TYA, 0, 0);
        TEST_CHECK("tya", 1, cycles == 2 && reg_get_acc() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);
}

