#include "test_op.h"
#include "test_check.h"
#include "cpu/cpu.h"
#include "opcode/optable.h"
#include "opcode/opcode.h"
#include "cpu/registers.h"
#include "cpu/memory.h"

static void
test_dec(void)
{
        int cycles;

        /* 1. check if 0xCE works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        mem_set(0x432, 11);
        cycles = op_exec(DEC_ABS, 0x32, 0x4);
        TEST_CHECK("dec", 1, cycles == 6 && mem_get(0x432) == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 2. check if ZERO_FLAG */
        mem_set(0x432, 1);
        cycles = op_exec(DEC_ABS, 0x32, 0x4);
        TEST_CHECK("dec", 2, cycles == 6 && mem_get(0x432) == 0 &&
                   reg_is_flag_set(ZERO_FLAG));
        cpu_reset(HARD_RESET);

        /* 3. check if NEG_FLAG */
        mem_set(0x432, 0);
        cycles = op_exec(DEC_ABS, 0x32, 0x4);
        TEST_CHECK("dec", 3, cycles == 6 && mem_get(0x432) == 0xFF &&
                   reg_is_flag_set(NEG_FLAG));
        cpu_reset(HARD_RESET);

        /* 4. check if 0xDE works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        mem_set(0x432, 11);
        reg_set_x(0x12);
        cycles = op_exec(DEC_ABSX, 0x20, 0x4);
        TEST_CHECK("dec", 4, cycles == 7 && mem_get(0x432) == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 5. check if 0xC6 works, NEG_FLAG and ZERO_FLAG shouldn't be set */ 
        mem_set(0x32, 11);
        cycles = op_exec(DEC_ZERO, 0x32, 0x0);
        TEST_CHECK("dec", 5, cycles == 5 && mem_get(0x32) == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 6. check if 0xD6 works, NEG_FLAG and ZERO_FLAG shouldn't be set */ 
        mem_set(0x32, 11);
        reg_set_x(0x12);
        cycles = op_exec(DEC_ZEROX, 0x20, 0x0);
        TEST_CHECK("dec", 6, cycles == 6 && mem_get(0x32) == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);
}

static void
test_dex(void)
{
        int cycles;

        /* 1. check if 0xCA works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_x(11);
        cycles = op_exec(DEX, 0, 0);
        TEST_CHECK("dex", 1, cycles == 2 && reg_get_x() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 2. check if ZERO_FLAG */
        reg_set_x(1);
        cycles = op_exec(DEX, 0, 0);
        TEST_CHECK("dex", 2, cycles == 2 && reg_get_x() == 0 &&
                   reg_is_flag_set(ZERO_FLAG));
        cpu_reset(HARD_RESET);

        /* 3. check if NEG_FLAG */
        reg_set_x(0);
        cycles = op_exec(DEX, 0, 0);
        TEST_CHECK("dex", 3, cycles == 2 && reg_get_x() == 0xFF &&
                   reg_is_flag_set(NEG_FLAG));
        cpu_reset(HARD_RESET);
}

static void
test_dey(void)
{
        int cycles;

        /* 1. check if 0x88 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_y(11);
        cycles = op_exec(DEY, 0, 0);
        TEST_CHECK("dey", 1, cycles == 2 && reg_get_y() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 2. check if ZERO_FLAG */
        reg_set_y(1);
        cycles = op_exec(DEY, 0, 0);
        TEST_CHECK("dey", 2, cycles == 2 && reg_get_y() == 0 &&
                   reg_is_flag_set(ZERO_FLAG));
        cpu_reset(HARD_RESET);

        /* 3. check if NEG_FLAG */
        reg_set_y(0);
        cycles = op_exec(DEY, 0, 0);
        TEST_CHECK("dey", 3, cycles == 2 && reg_get_y() == 0xFF &&
                   reg_is_flag_set(NEG_FLAG));
        cpu_reset(HARD_RESET);
}

static void
test_inc(void)
{
        int cycles;

        /* 1. check if 0xEE works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        mem_set(0x432, 9);
        cycles = op_exec(INC_ABS, 0x32, 0x4);
        TEST_CHECK("inc", 1, cycles == 6 && mem_get(0x432) == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 2. check if ZERO_FLAG */
        mem_set(0x432, 0xFF);
        cycles = op_exec(INC_ABS, 0x32, 0x4);
        TEST_CHECK("inc", 2, cycles == 6 && mem_get(0x432) == 0 &&
                   reg_is_flag_set(ZERO_FLAG));
        cpu_reset(HARD_RESET);

        /* 3. check if NEG_FLAG */
        mem_set(0x432, 0xFE);
        cycles = op_exec(INC_ABS, 0x32, 0x4);
        TEST_CHECK("inc", 3, cycles == 6 && mem_get(0x432) == 0xFF &&
                   reg_is_flag_set(NEG_FLAG));
        cpu_reset(HARD_RESET);

        /* 4. check if 0xFE works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        mem_set(0x432, 9);
        reg_set_x(0x12);
        cycles = op_exec(INC_ABSX, 0x20, 0x4);
        TEST_CHECK("inc", 4, cycles == 7 && mem_get(0x432) == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 5. check if 0xE6 works, NEG_FLAG and ZERO_FLAG shouldn't be set */ 
        mem_set(0x32, 9);
        cycles = op_exec(INC_ZERO, 0x32, 0x0);
        TEST_CHECK("inc", 5, cycles == 5 && mem_get(0x32) == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 6. check if 0xF6 works, NEG_FLAG and ZERO_FLAG shouldn't be set */ 
        mem_set(0x32, 9);
        reg_set_x(0x12);
        cycles = op_exec(INC_ZEROX, 0x20, 0x0);
        TEST_CHECK("inc", 6, cycles == 6 && mem_get(0x32) == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);
}

static void
test_inx(void)
{
        int cycles;

        /* 1. check if 0xE8 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_x(9);
        cycles = op_exec(INX, 0, 0);
        TEST_CHECK("inx", 1, cycles == 2 && reg_get_x() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 2. check if ZERO_FLAG */
        reg_set_x(0xFF);
        cycles = op_exec(INX, 0, 0);
        TEST_CHECK("inx", 2, cycles == 2 && reg_get_x() == 0 &&
                   reg_is_flag_set(ZERO_FLAG));
        cpu_reset(HARD_RESET);

        /* 3. check if NEG_FLAG */
        reg_set_x(0xFE);
        cycles = op_exec(INX, 0, 0);
        TEST_CHECK("inx", 3, cycles == 2 && reg_get_x() == 0xFF &&
                   reg_is_flag_set(NEG_FLAG));
        cpu_reset(HARD_RESET);
}

static void
test_iny(void)
{
        int cycles;

        /* 1. check if 0xC8 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_y(9);
        cycles = op_exec(INY, 0, 0);
        TEST_CHECK("iny", 1, cycles == 2 && reg_get_y() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 2. check if ZERO_FLAG */
        reg_set_y(0xFF);
        cycles = op_exec(INY, 0, 0);
        TEST_CHECK("iny", 2, cycles == 2 && reg_get_y() == 0 &&
                   reg_is_flag_set(ZERO_FLAG));
        cpu_reset(HARD_RESET);

        /* 3. check if NEG_FLAG */
        reg_set_y(0xFE);
        cycles = op_exec(INY, 0, 0);
        TEST_CHECK("iny", 3, cycles == 2 && reg_get_y() == 0xFF &&
                   reg_is_flag_set(NEG_FLAG));
        cpu_reset(HARD_RESET);
}

void
test_op_incdec(void)
{
        test_dec();
        test_dex();
        test_dey();
        test_inc();
        test_inx();
        test_iny();
}
