#include "test.h"
#include "test_cpu.h"
#include "cpu/registers.h"

static int error_state = 0;

void
test_sys(void)
{
        test_regs();
        test_mem();
        test_stack();
}

void
test_set_err(int val)
{
        error_state = val;
}

int
test_get_err(void)
{
        return error_state;
}
