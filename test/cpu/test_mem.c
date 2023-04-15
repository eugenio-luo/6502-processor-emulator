#include "test_cpu.h"
#include "test_check.h"
#include "cpu/memory.h"

void
test_cpu_mem(void)
{
        /* 1. check if initial state is correct and if mem_get works */
        int empty = 1;
        for (int i = 0; i < RAM_SIZE; ++i) {
                if (mem_get(i)) {
                        empty = 0;
                        break;
                }
        }
        TEST_CHECK("mem", 1, empty);

        /* 2-4. check if mirrors addresses works and if mem_set works */
        mem_set(0x173, 0xFF);
        TEST_CHECK("mem", 2, mem_get(0x973) == 0xFF);
        TEST_CHECK("mem", 3, mem_get(0x1173) == 0xFF);
        TEST_CHECK("mem", 4, mem_get(0x1973) == 0xFF);

        /* 5. check if soft reset state is correct */
        cpu_reset(SOFT_RESET);
        TEST_CHECK("mem", 5, mem_get(0x173) == 0xFF);

        cpu_reset(HARD_RESET);
}
