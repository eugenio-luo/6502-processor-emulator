#include "test_op.h"
#include "test_check.h"
#include "cpu/cpu.h"
#include "opcode/optable.h"
#include "opcode/opcode.h"
#include "cpu/registers.h"
#include "cpu/memory.h"

static void
test_and(void)
{
        int cycles;

        /* 1. check if 0x29 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_acc(3);
        cycles = op_exec(AND_IMM, 5, 0);
        TEST_CHECK("and", 1, cycles == 2 && reg_get_acc() == 1 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);
  
        /* 2. check if ZERO_FLAG get set with zero as 0x29 argument */
        reg_set_acc(8);
        cycles = op_exec(AND_IMM, 5, 0);
        TEST_CHECK("and", 2, cycles == 2 && reg_get_acc() == 0 &&
                   reg_is_flag_set(ZERO_FLAG));
        cpu_reset(HARD_RESET);
        
        /* 3. check if NEG_FLAG get set with negative number as 0x29 argument */
        reg_set_acc(0x83);
        cycles = op_exec(AND_IMM, 0x86, 0);
        TEST_CHECK("and", 3, cycles == 2 && reg_get_acc() == 0x82 &&
                   reg_is_flag_set(NEG_FLAG));
        cpu_reset(HARD_RESET);

        /* 4. check if 0x2D works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_acc(3);
        mem_set(0x6FF, 5);
        cycles = op_exec(AND_ABS, 0xFF, 0x6);
        TEST_CHECK("and", 4, cycles == 4 && reg_get_acc() == 1 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 5. check if 0x3D works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_acc(3);
        mem_set(0x6FF, 5);
        reg_set_x(0x1F);
        cycles = op_exec(AND_ABSX, 0xE0, 0x6);
        TEST_CHECK("and", 5, cycles == 4 && reg_get_acc() == 1 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 6. check if 0x3D cycles increases if page boundary is crossed */
        reg_set_acc(3);
        mem_set(0x70F, 5);
        reg_set_x(0x1F);
        cycles = op_exec(AND_ABSX, 0xF0, 0x6);
        TEST_CHECK("and", 6, cycles == 5 && reg_get_acc() == 1 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 7. check if 0x39 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_acc(3);
        mem_set(0x6FF, 5);
        reg_set_y(0x1F);
        cycles = op_exec(AND_ABSY, 0xE0, 0x6);
        TEST_CHECK("and", 7, cycles == 4 && reg_get_acc() == 1 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 8. check if 0x39 cycles increases if page boundary is crossed */
        reg_set_acc(3);
        mem_set(0x70F, 5);
        reg_set_y(0x1F);
        cycles = op_exec(AND_ABSY, 0xF0, 0x6);
        TEST_CHECK("and", 8, cycles == 5 && reg_get_acc() == 1 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 9. check if 0x25 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_acc(3);
        mem_set(0x85, 5);
        cycles = op_exec(AND_ZERO, 0x85, 0);
        TEST_CHECK("and", 9, cycles == 3 && reg_get_acc() == 1 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 10. check if 0x35 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_acc(3);
        mem_set(0x85, 5);
        reg_set_x(0x10);
        cycles = op_exec(AND_ZEROX, 0x75, 0);
        TEST_CHECK("and", 10, cycles == 4 && reg_get_acc() == 1 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 11. check if 0x21 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_acc(3);
        mem_set(0x85, 0x32);
        mem_set(0x86, 0x4);
        mem_set(0x432, 5);
        reg_set_x(0x2);
        cycles = op_exec(AND_INDX_INDR, 0x83, 0);
        TEST_CHECK("and", 11, cycles == 6 && reg_get_acc() == 1 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 12. check if 0x31 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_acc(3);
        mem_set(0x85, 0x30);
        mem_set(0x86, 0x4);
        mem_set(0x432, 5);
        reg_set_y(0x2);
        cycles = op_exec(AND_INDR_INDY, 0x85, 0);
        TEST_CHECK("and", 12, cycles == 5 && reg_get_acc() == 1 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 13. check if 0x31 cycles increases if page boundary is crossed */
        reg_set_acc(3);
        mem_set(0x85, 0xFF);
        mem_set(0x86, 0x4);
        mem_set(0x501, 5);
        reg_set_y(0x2);
        cycles = op_exec(AND_INDR_INDY, 0x85, 0);
        TEST_CHECK("and", 13, cycles == 6 && reg_get_acc() == 1 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);
}

static void
test_bit(void)
{
        int cycles;

        /* 1. check if 0x2C works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_acc(0x65);
        mem_set(0x432, 0x63);
        cycles = op_exec(BIT_ABS, 0x32, 4);
        TEST_CHECK("bit", 1, cycles == 4 && reg_is_flag_set(OVER_FLAG) &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);
        
        /* 2. check if ZERO_FLAG get set with zero as 0x2C argument */
        reg_set_acc(0x0);
        mem_set(0x432, 0x63);
        cycles = op_exec(BIT_ABS, 0x32, 4);
        TEST_CHECK("bit", 2, cycles == 4 && reg_is_flag_set(ZERO_FLAG) &&
                   ( !reg_is_flag_set(NEG_FLAG | OVER_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 3. check if NEG_FLAG get set with negative number as 0x2C argument */
        reg_set_acc(0x83);
        mem_set(0x432, 0x80);
        cycles = op_exec(BIT_ABS, 0x32, 4);
        TEST_CHECK("bit", 3, cycles == 4 && reg_is_flag_set(NEG_FLAG) &&
                   ( !reg_is_flag_set(ZERO_FLAG | OVER_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 4. check if 0x2C works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_acc(0x65);
        mem_set(0x32, 0x63);
        cycles = op_exec(BIT_ZERO, 0x32, 0);
        TEST_CHECK("bit", 4, cycles == 3 && reg_is_flag_set(OVER_FLAG) &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);
}

void
test_op_logic(void)
{
        test_and();
        test_bit();
}
