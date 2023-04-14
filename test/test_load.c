#include "test_op.h"
#include "test_check.h"
#include "cpu/cpu.h"
#include "opcode/optable.h"
#include "opcode/opcode.h"
#include "cpu/registers.h"
#include "cpu/memory.h"

static void
test_lda(void)
{
        int cycles;

        /* 1. check if 0xA9 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        cycles = op_exec(LDA_IMM, 10, 0);
        TEST_CHECK("lda", 1, cycles == 2 && reg_get_acc() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 2. check if ZERO_FLAG get set with zero number as 0xA9 argument */
        cycles = op_exec(LDA_IMM, 0, 0);  
        TEST_CHECK("lda", 2, cycles == 2 && reg_get_acc() == 0 &&
                   reg_is_flag_set(ZERO_FLAG));
        cpu_reset(HARD_RESET);

        /* 3. check if NEG_FLAG get set with negative number as 0xA9 argument */
        cycles = op_exec(LDA_IMM, -1, 0);  
        TEST_CHECK("lda", 3, cycles == 2 && reg_get_acc() == 0xFF &&
                   reg_is_flag_set(NEG_FLAG));
        cpu_reset(HARD_RESET);

        /* 4. check if 0xAD works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        mem_set(0x6FF, 10);
        cycles = op_exec(LDA_ABS, 0xFF, 0x6);
        TEST_CHECK("lda", 4, cycles == 4 && reg_get_acc() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 5. check if 0xBD works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        mem_set(0x6FF, 10);
        reg_set_x(0x1F);
        cycles = op_exec(LDA_ABSX, 0xE0, 0x6);
        TEST_CHECK("lda", 5, cycles == 4 && reg_get_acc() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 6. check if 0xBD cycles increases if page boundary is crossed */
        mem_set(0x70F, 10);
        reg_set_x(0x1F);
        cycles = op_exec(LDA_ABSX, 0xF0, 0x6);
        TEST_CHECK("lda", 6, cycles == 5 && reg_get_acc() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 7. check if 0xB9 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        mem_set(0x6FF, 10);
        reg_set_y(0x1F);
        cycles = op_exec(LDA_ABSY, 0xE0, 0x6);
        TEST_CHECK("lda", 7, cycles == 4 && reg_get_acc() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 8. check if 0xB9 cycles increases if page boundary is crossed */
        mem_set(0x70F, 10);
        reg_set_y(0x1F);
        cycles = op_exec(LDA_ABSY, 0xF0, 0x6);
        TEST_CHECK("lda", 8, cycles == 5 && reg_get_acc() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 9. check if 0xA5 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        mem_set(0x85, 10);
        cycles = op_exec(LDA_ZERO, 0x85, 0);
        TEST_CHECK("lda", 9, cycles == 3 && reg_get_acc() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 10. check if 0xB5 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        mem_set(0x85, 10);
        reg_set_x(0x10);
        cycles = op_exec(LDA_ZEROX, 0x75, 0);
        TEST_CHECK("lda", 10, cycles == 4 && reg_get_acc() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 11. check if 0xB5 wraps around */
        mem_set(0x1, 10);
        reg_set_x(0x10);
        cycles = op_exec(LDA_ZEROX, 0xF1, 0);
        TEST_CHECK("lda", 11, cycles == 4 && reg_get_acc() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 12. check if 0xA1 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        mem_set(0x85, 0x32);
        mem_set(0x86, 0x4);
        mem_set(0x432, 10);
        reg_set_x(0x2);
        cycles = op_exec(LDA_INDX_INDR, 0x83, 0);
        TEST_CHECK("lda", 12, cycles == 6 && reg_get_acc() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 13. check if 0xB1 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        mem_set(0x85, 0x30);
        mem_set(0x86, 0x4);
        mem_set(0x432, 10);
        reg_set_y(0x2);
        cycles = op_exec(LDA_INDR_INDY, 0x85, 0);
        TEST_CHECK("lda", 13, cycles == 5 && reg_get_acc() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 14. check if 0xB1 cycles increases if page boundary is crossed */
        mem_set(0x85, 0xFF);
        mem_set(0x86, 0x4);
        mem_set(0x501, 10);
        reg_set_y(0x2);
        cycles = op_exec(LDA_INDR_INDY, 0x85, 0);
        TEST_CHECK("lda", 14, cycles == 6 && reg_get_acc() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);
}

static void
test_ldx(void)
{
        int cycles;
        
        /* 1. check if 0xA2 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        cycles = op_exec(LDX_IMM, 10, 0);
        TEST_CHECK("ldx", 1, cycles == 2 && reg_get_x() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 2. check if ZERO_FLAG get set with zero number as 0xA2 argument */
        cycles = op_exec(LDX_IMM, 0, 0);  
        TEST_CHECK("ldx", 2, cycles == 2 && reg_get_x() == 0 &&
                   reg_is_flag_set(ZERO_FLAG));
        cpu_reset(HARD_RESET);

        /* 3. check if NEG_FLAG get set with negative number as 0xA2 argument */
        cycles = op_exec(LDX_IMM, -1, 0);  
        TEST_CHECK("ldx", 3, cycles == 2 && reg_get_x() == 0xFF &&
                   reg_is_flag_set(NEG_FLAG));
        cpu_reset(HARD_RESET);

        /* 4. check if 0xAE works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        mem_set(0x6FF, 10);
        cycles = op_exec(LDX_ABS, 0xFF, 0x6);
        TEST_CHECK("ldx", 4, cycles == 4 && reg_get_x() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 5. check if 0xBE works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        mem_set(0x6FF, 10);
        reg_set_y(0x1F);
        cycles = op_exec(LDX_ABSY, 0xE0, 0x6);
        TEST_CHECK("ldx", 5, cycles == 4 && reg_get_x() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 6. check if 0xBE cycles increases if page boundary is crossed */
        mem_set(0x70F, 10);
        reg_set_y(0x1F);
        cycles = op_exec(LDX_ABSY, 0xF0, 0x6);
        TEST_CHECK("ldx", 6, cycles == 5 && reg_get_x() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 7. check if 0xA6 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        mem_set(0x85, 10);
        cycles = op_exec(LDX_ZERO, 0x85, 0);
        TEST_CHECK("ldx", 7, cycles == 3 && reg_get_x() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 8. check if 0xB6 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        mem_set(0x85, 10);
        reg_set_y(0x10);
        cycles = op_exec(LDX_ZEROY, 0x75, 0);
        TEST_CHECK("ldx", 8, cycles == 4 && reg_get_x() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 9. check if 0xB6 wraps around */
        mem_set(0x1, 10);
        reg_set_y(0x10);
        cycles = op_exec(LDX_ZEROY, 0xF1, 0);
        TEST_CHECK("ldx", 9, cycles == 4 && reg_get_x() == 10 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);
}

void
test_load(void)
{
        test_lda();
        test_ldx();
}
