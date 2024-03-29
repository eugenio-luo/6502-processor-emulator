#include "test_cpu.h"
#include "test_check.h"
#include "cpu/registers.h"
#include "cpu/cpu.h"

void
test_cpu_regs(void)
{
        /* 1-3. check if initial state is correct and if reg_get works */
        TEST_CHECK("regs", 1, reg_get_flags() == (INT_DISABLE | BREAK_COM0 | BREAK_COM1));
        TEST_CHECK("regs", 2, reg_get_acc() == 0 && reg_get_x() == 0 && reg_get_y() == 0);
        TEST_CHECK("regs", 3, reg_get_sp() == INIT_STACK_PTR);

        /* 4-6. check if soft reset state is correct and if reg_set, reg_clear_flags work */
        reg_set_x(10);
        reg_clear_flags(INT_DISABLE);
        cpu_reset(SOFT_RESET);
        TEST_CHECK("regs", 4, reg_get_x() == 10);
        TEST_CHECK("regs", 5, reg_get_sp() == INIT_STACK_PTR - 3);
        TEST_CHECK("regs", 6, reg_get_flags() == (INT_DISABLE | BREAK_COM0 | BREAK_COM1));

        cpu_reset(HARD_RESET);
}
