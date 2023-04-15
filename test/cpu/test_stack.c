#include "test_check.h"
#include "test_cpu.h"
#include "cpu/stack.h"
#include "cpu/registers.h"
#include "cpu/cpu.h"
#include "cpu/memory.h"

void
test_cpu_stack(void)
{
        /* initial state is already checked by test_regs and test_mem */

        /* 1. check if stack_push and stack_top works */
        stack_push(0xFF);
        stack_push(0xFD);
        TEST_CHECK("stack", 1, stack_top() == 0xFD);
        
        /* 2. check if stack_pop works */
        stack_pop();
        TEST_CHECK("stack", 2, stack_top() == 0xFF);

        /* 3. check if underflow works */
        stack_pop();
        stack_pop();
        stack_pop();
        stack_pop();
        TEST_CHECK("stack", 3, reg_get_sp() == 0x0);
        cpu_reset(HARD_RESET);
        
        /* 4. check if overflow works */
        for (int i = 0; i < INIT_STACK_PTR + 1; ++i)
                stack_push(1);
        TEST_CHECK("stack", 4, reg_get_sp() == 0xFF);
        cpu_reset(HARD_RESET);
        
        /* 5. check if right place in memory */
        stack_push(0xFF);
        TEST_CHECK("stack", 5, mem_get(0x100 + INIT_STACK_PTR) == 0xFF);
        
        cpu_reset(HARD_RESET);
}

