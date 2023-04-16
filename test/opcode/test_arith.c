#include "test_op.h"
#include "test_check.h"
#include "cpu/cpu.h"
#include "opcode/optable.h"
#include "opcode/opcode.h"
#include "cpu/registers.h"
#include "cpu/memory.h"

static void
test_adc(void)
{
        int cycles;

        /* 1. check if 0x69 works, NEG_FLAG, ZERO_FLAG, CARRY_FLAG and 
              OVER_FLAG shouldn't be set */
        reg_set_acc(3);
        cycles = op_exec(ADC_IMM, 5, 0);
        TEST_CHECK("adc", 1, cycles == 2 && reg_get_acc() == 8 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG | OVER_FLAG | CARRY_FLAG) ));
        cpu_reset(HARD_RESET);
  
        /* 2. check if ZERO_FLAG, CARRY_FLAG and OVER_FLAG get set with 
              zero as 0x69 argument */
        reg_set_acc(0xFF);
        cycles = op_exec(ADC_IMM, 1, 0);
        TEST_CHECK("adc", 2, cycles == 2 && reg_get_acc() == 0 &&
                   reg_is_flag_set(ZERO_FLAG | CARRY_FLAG | OVER_FLAG));
        cpu_reset(HARD_RESET);
        
        /* 3. check if NEG_FLAG get set with negative number as 0x69 argument */
        reg_set_acc(0x80);
        cycles = op_exec(ADC_IMM, 0x13, 0);
        TEST_CHECK("adc", 3, cycles == 2 && reg_get_acc() == 0x93 &&
                   reg_is_flag_set(NEG_FLAG));
        cpu_reset(HARD_RESET);

        /* 4. check if 0x6D works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_acc(3);
        mem_set(0x6FF, 5);
        cycles = op_exec(ADC_ABS, 0xFF, 0x6);
        TEST_CHECK("adc", 4, cycles == 4 && reg_get_acc() == 8 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 5. check if 0x7D works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_acc(3);
        mem_set(0x6FF, 5);
        reg_set_x(0x1F);
        cycles = op_exec(ADC_ABSX, 0xE0, 0x6);
        TEST_CHECK("adc", 5, cycles == 4 && reg_get_acc() == 8 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 6. check if 0x7D cycles increases if page boundary is crossed */
        reg_set_acc(3);
        mem_set(0x70F, 5);
        reg_set_x(0x1F);
        cycles = op_exec(ADC_ABSX, 0xF0, 0x6);
        TEST_CHECK("adc", 6, cycles == 5 && reg_get_acc() == 8 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 7. check if 0x79 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_acc(3);
        mem_set(0x6FF, 5);
        reg_set_y(0x1F);
        cycles = op_exec(ADC_ABSY, 0xE0, 0x6);
        TEST_CHECK("adc", 7, cycles == 4 && reg_get_acc() == 8 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 8. check if 0x79 cycles increases if page boundary is crossed */
        reg_set_acc(3);
        mem_set(0x70F, 5);
        reg_set_y(0x1F);
        cycles = op_exec(ADC_ABSY, 0xF0, 0x6);
        TEST_CHECK("adc", 8, cycles == 5 && reg_get_acc() == 8 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 9. check if 0x65 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_acc(3);
        mem_set(0x85, 5);
        cycles = op_exec(ADC_ZERO, 0x85, 0);
        TEST_CHECK("adc", 9, cycles == 3 && reg_get_acc() == 8 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 10. check if 0x65 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_acc(3);
        mem_set(0x85, 5);
        reg_set_x(0x10);
        cycles = op_exec(ADC_ZEROX, 0x75, 0);
        TEST_CHECK("adc", 10, cycles == 4 && reg_get_acc() == 8 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 11. check if 0x61 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_acc(3);
        mem_set(0x85, 0x32);
        mem_set(0x86, 0x4);
        mem_set(0x432, 5);
        reg_set_x(0x2);
        cycles = op_exec(ADC_INDX_INDR, 0x83, 0);
        TEST_CHECK("adc", 11, cycles == 6 && reg_get_acc() == 8 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 12. check if 0x71 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_acc(3);
        mem_set(0x85, 0x30);
        mem_set(0x86, 0x4);
        mem_set(0x432, 5);
        reg_set_y(0x2);
        cycles = op_exec(ADC_INDR_INDY, 0x85, 0);
        TEST_CHECK("adc", 12, cycles == 5 && reg_get_acc() == 8 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 13. check if 0x71 cycles increases if page boundary is crossed */
        reg_set_acc(3);
        mem_set(0x85, 0xFF);
        mem_set(0x86, 0x4);
        mem_set(0x501, 5);
        reg_set_y(0x2);
        cycles = op_exec(ADC_INDR_INDY, 0x85, 0);
        TEST_CHECK("adc", 13, cycles == 6 && reg_get_acc() == 8 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);
}

void
test_op_arith(void)
{
        test_adc();
}
