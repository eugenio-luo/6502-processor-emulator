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
        reg_set_acc(0x80);
        cycles = op_exec(ADC_IMM, 0x80, 0);
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

        /* 10. check if 0x75 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
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

static void
test_cmp(void)
{
        int cycles;

        /* 1. check if 0xC9 works, NEG_FLAG, ZERO_FLAG, CARRY_FLAG 
              shouldn't be set */
        reg_set_acc(0x3);
        cycles = op_exec(CMP_IMM, 0xF5, 0);
        TEST_CHECK("cmp", 1, cycles == 2 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG | CARRY_FLAG) ));
        cpu_reset(HARD_RESET);
  
        /* 2. check if ZERO_FLAG get set */
        reg_set_acc(0x4);
        cycles = op_exec(CMP_IMM, 4, 0);
        TEST_CHECK("cmp", 2, cycles == 2 && reg_is_flag_set(ZERO_FLAG));
        cpu_reset(HARD_RESET);
        
        /* 3. check if NEG_FLAG and CARRY FLAG get set */
        reg_set_acc(0xF3);
        cycles = op_exec(CMP_IMM, 0x5, 0);
        TEST_CHECK("cmp", 3, cycles == 2 &&
                   reg_is_flag_set(NEG_FLAG | CARRY_FLAG));
        cpu_reset(HARD_RESET);

        /* 4. check if 0xCD works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_acc(5);
        mem_set(0x6FF, 3);
        cycles = op_exec(CMP_ABS, 0xFF, 0x6);
        TEST_CHECK("cmp", 4, cycles == 4 && reg_is_flag_set(CARRY_FLAG) &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 5. check if 0xDD works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_acc(5);
        mem_set(0x6FF, 3);
        reg_set_x(0x1F);
        cycles = op_exec(CMP_ABSX, 0xE0, 0x6);
        TEST_CHECK("cmp", 5, cycles == 4 && reg_is_flag_set(CARRY_FLAG) &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 6. check if 0xDD cycles increases if page boundary is crossed */
        reg_set_acc(5);
        mem_set(0x70F, 3);
        reg_set_x(0x1F);
        cycles = op_exec(CMP_ABSX, 0xF0, 0x6);
        TEST_CHECK("cmp", 6, cycles == 5 && reg_is_flag_set(CARRY_FLAG) &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 7. check if 0xD9 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_acc(5);
        mem_set(0x6FF, 3);
        reg_set_y(0x1F);
        cycles = op_exec(CMP_ABSY, 0xE0, 0x6);
        TEST_CHECK("cmp", 7, cycles == 4 && reg_is_flag_set(CARRY_FLAG) &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 8. check if 0xD9 cycles increases if page boundary is crossed */
        reg_set_acc(5);
        mem_set(0x70F, 3);
        reg_set_y(0x1F);
        cycles = op_exec(CMP_ABSY, 0xF0, 0x6);
        TEST_CHECK("cmp", 8, cycles == 5 && reg_is_flag_set(CARRY_FLAG) &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 9. check if 0xC5 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_acc(5);
        mem_set(0x85, 3);
        cycles = op_exec(CMP_ZERO, 0x85, 0);
        TEST_CHECK("cmp", 9, cycles == 3 && reg_is_flag_set(CARRY_FLAG) &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 10. check if 0xD5 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_acc(5);
        mem_set(0x85, 3);
        reg_set_x(0x10);
        cycles = op_exec(CMP_ZEROX, 0x75, 0);
        TEST_CHECK("cmp", 10, cycles == 4 && reg_is_flag_set(CARRY_FLAG) &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 11. check if 0xC1 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_acc(5);
        mem_set(0x85, 0x32);
        mem_set(0x86, 0x4);
        mem_set(0x432, 3);
        reg_set_x(0x2);
        cycles = op_exec(CMP_INDX_INDR, 0x83, 0);
        TEST_CHECK("cmp", 11, cycles == 6 && reg_is_flag_set(CARRY_FLAG) &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 12. check if 0xD1 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_acc(5);
        mem_set(0x85, 0x30);
        mem_set(0x86, 0x4);
        mem_set(0x432, 3);
        reg_set_y(0x2);
        cycles = op_exec(CMP_INDR_INDY, 0x85, 0);
        TEST_CHECK("cmp", 12, cycles == 5 && reg_is_flag_set(CARRY_FLAG) &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 13. check if 0xD1 cycles increases if page boundary is crossed */
        reg_set_acc(5);
        mem_set(0x85, 0xFF);
        mem_set(0x86, 0x4);
        mem_set(0x501, 3);
        reg_set_y(0x2);
        cycles = op_exec(CMP_INDR_INDY, 0x85, 0);
        TEST_CHECK("cmp", 13, cycles == 6 && reg_is_flag_set(CARRY_FLAG) &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);
}

static void
test_cpx(void)
{
        int cycles;

        /* 1. check if 0xE0 works, NEG_FLAG, ZERO_FLAG, CARRY_FLAG 
              shouldn't be set */
        reg_set_x(0x3);
        cycles = op_exec(CPX_IMM, 0xF5, 0);
        TEST_CHECK("cpx", 1, cycles == 2 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG | CARRY_FLAG) ));
        cpu_reset(HARD_RESET);
  
        /* 2. check if ZERO_FLAG get set */
        reg_set_x(0x4);
        cycles = op_exec(CPX_IMM, 4, 0);
        TEST_CHECK("cpx", 2, cycles == 2 && reg_is_flag_set(ZERO_FLAG));
        cpu_reset(HARD_RESET);
        
        /* 3. check if NEG_FLAG and CARRY FLAG get set */
        reg_set_x(0xF3);
        cycles = op_exec(CPX_IMM, 0x5, 0);
        TEST_CHECK("cpx", 3, cycles == 2 &&
                   reg_is_flag_set(NEG_FLAG | CARRY_FLAG));
        cpu_reset(HARD_RESET);

        /* 4. check if 0xEC works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_x(5);
        mem_set(0x6FF, 3);
        cycles = op_exec(CPX_ABS, 0xFF, 0x6);
        TEST_CHECK("cpx", 4, cycles == 4 && reg_is_flag_set(CARRY_FLAG) &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 5. check if 0xE4 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_x(5);
        mem_set(0x85, 3);
        cycles = op_exec(CPX_ZERO, 0x85, 0);
        TEST_CHECK("cpx", 5, cycles == 3 && reg_is_flag_set(CARRY_FLAG) &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);
}

static void
test_cpy(void)
{
        int cycles;

        /* 1. check if 0xC0 works, NEG_FLAG, ZERO_FLAG, CARRY_FLAG 
              shouldn't be set */
        reg_set_y(0x3);
        cycles = op_exec(CPY_IMM, 0xF5, 0);
        TEST_CHECK("cpy", 1, cycles == 2 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG | CARRY_FLAG) ));
        cpu_reset(HARD_RESET);
  
        /* 2. check if ZERO_FLAG get set */
        reg_set_y(0x4);
        cycles = op_exec(CPY_IMM, 4, 0);
        TEST_CHECK("cpy", 2, cycles == 2 && reg_is_flag_set(ZERO_FLAG));
        cpu_reset(HARD_RESET);
        
        /* 3. check if NEG_FLAG and CARRY FLAG get set */
        reg_set_y(0xF3);
        cycles = op_exec(CPY_IMM, 0x5, 0);
        TEST_CHECK("cpy", 3, cycles == 2 &&
                   reg_is_flag_set(NEG_FLAG | CARRY_FLAG));
        cpu_reset(HARD_RESET);

        /* 4. check if 0xCC works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_y(5);
        mem_set(0x6FF, 3);
        cycles = op_exec(CPY_ABS, 0xFF, 0x6);
        TEST_CHECK("cpy", 4, cycles == 4 && reg_is_flag_set(CARRY_FLAG) &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 5. check if 0xC4 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_y(5);
        mem_set(0x85, 3);
        cycles = op_exec(CPY_ZERO, 0x85, 0);
        TEST_CHECK("cpy", 5, cycles == 3 && reg_is_flag_set(CARRY_FLAG) &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);
}

static void
test_sbc(void)
{
        int cycles;

        /* 1. check if 0xE9 works, NEG_FLAG, ZERO_FLAG, OVER_FLAG
              shouldn't be set while CARRY_FLAG should be */
        reg_set_flags(CARRY_FLAG);
        reg_set_acc(5);
        cycles = op_exec(SBC_IMM, 3, 0);
        TEST_CHECK("sbc", 1, cycles == 2 && reg_get_acc() == 2 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG | OVER_FLAG) ) &&
                     reg_is_flag_set(CARRY_FLAG));
        cpu_reset(HARD_RESET);

        /* 2. check if ZERO_FLAG get set */
        reg_set_flags(CARRY_FLAG);
        reg_set_acc(0x80);
        cycles = op_exec(SBC_IMM, 0x80, 0);
        TEST_CHECK("sbc", 2, cycles == 2 && reg_get_acc() == 0 &&
                   reg_is_flag_set(ZERO_FLAG));
        cpu_reset(HARD_RESET);

        /* 3. check if OVER_FLAG get set */
        reg_set_flags(CARRY_FLAG);
        reg_set_acc(0x50);
        cycles = op_exec(SBC_IMM, 0xB0, 0);
        TEST_CHECK("sbc", 3, cycles == 2 && reg_get_acc() == 0xA0 &&
                   reg_is_flag_set(OVER_FLAG));
        cpu_reset(HARD_RESET);
        
        /* 4. check if 0xED works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_flags(CARRY_FLAG);
        reg_set_acc(5);
        mem_set(0x6FF, 3);
        cycles = op_exec(SBC_ABS, 0xFF, 0x6);
        TEST_CHECK("sbc", 4, cycles == 4 && reg_get_acc() == 2 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 5. check if 0xFD works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_flags(CARRY_FLAG);
        reg_set_acc(5);
        mem_set(0x6FF, 3);
        reg_set_x(0x1F);
        cycles = op_exec(SBC_ABSX, 0xE0, 0x6);
        TEST_CHECK("sbc", 5, cycles == 4 && reg_get_acc() == 2 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 6. check if 0xFD cycles increases if page boundary is crossed */
        reg_set_flags(CARRY_FLAG);
        reg_set_acc(5);
        mem_set(0x70F, 3);
        reg_set_x(0x1F);
        cycles = op_exec(SBC_ABSX, 0xF0, 0x6);
        TEST_CHECK("sbc", 6, cycles == 5 && reg_get_acc() == 2 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 7. check if 0xF9 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_flags(CARRY_FLAG);
        reg_set_acc(5);
        mem_set(0x6FF, 3);
        reg_set_y(0x1F);
        cycles = op_exec(SBC_ABSY, 0xE0, 0x6);
        TEST_CHECK("sbc", 7, cycles == 4 && reg_get_acc() == 2 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 8. check if 0xF9 cycles increases if page boundary is crossed */
        reg_set_flags(CARRY_FLAG);
        reg_set_acc(5);
        mem_set(0x70F, 3);
        reg_set_y(0x1F);
        cycles = op_exec(SBC_ABSY, 0xF0, 0x6);
        TEST_CHECK("sbc", 8, cycles == 5 && reg_get_acc() == 2 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 9. check if 0xE5 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_flags(CARRY_FLAG);
        reg_set_acc(5);
        mem_set(0x85, 3);
        cycles = op_exec(SBC_ZERO, 0x85, 0);
        TEST_CHECK("sbc", 9, cycles == 3 && reg_get_acc() == 2 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 10. check if 0xF5 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_flags(CARRY_FLAG);
        reg_set_acc(5);
        mem_set(0x85, 3);
        reg_set_x(0x10);
        cycles = op_exec(SBC_ZEROX, 0x75, 0);
        TEST_CHECK("sbc", 10, cycles == 4 && reg_get_acc() == 2 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 11. check if 0xE1 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_flags(CARRY_FLAG);
        reg_set_acc(5);
        mem_set(0x85, 0x32);
        mem_set(0x86, 0x4);
        mem_set(0x432, 3);
        reg_set_x(0x2);
        cycles = op_exec(SBC_INDX_INDR, 0x83, 0);
        TEST_CHECK("sbc", 11, cycles == 6 && reg_get_acc() == 2 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 12. check if 0xF1 works, NEG_FLAG and ZERO_FLAG shouldn't be set */
        reg_set_flags(CARRY_FLAG);
        reg_set_acc(5);
        mem_set(0x85, 0x30);
        mem_set(0x86, 0x4);
        mem_set(0x432, 3);
        reg_set_y(0x2);
        cycles = op_exec(SBC_INDR_INDY, 0x85, 0);
        TEST_CHECK("sbc", 12, cycles == 5 && reg_get_acc() == 2 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);

        /* 13. check if 0xF1 cycles increases if page boundary is crossed */
        reg_set_flags(CARRY_FLAG);
        reg_set_acc(5);
        mem_set(0x85, 0xFF);
        mem_set(0x86, 0x4);
        mem_set(0x501, 3);
        reg_set_y(0x2);
        cycles = op_exec(SBC_INDR_INDY, 0x85, 0);
        TEST_CHECK("sbc", 13, cycles == 6 && reg_get_acc() == 2 &&
                   ( !reg_is_flag_set(NEG_FLAG | ZERO_FLAG) ));
        cpu_reset(HARD_RESET);
}

void
test_op_arith(void)
{
        test_adc();
        test_cmp();
        test_cpx();
        test_cpy();
        test_sbc();
}
