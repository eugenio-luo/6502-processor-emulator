#include <stdio.h>

#include "test_op.h"
#include "test_check.h"
#include "cpu/cpu.h"
#include "opcode/optable.h"
#include "opcode/opcode.h"
#include "cpu/registers.h"

static void
test_lda(void)
{
        int cycles;

        /* 1. check if 0xA9 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        cycles = op_exec(LDA_IMM, 10, 0);
        printf("%x\n", reg_is_flag_set(NEG_FLAG | ZERO_FLAG));
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
}

void
test_load(void)
{
        test_lda();
}
