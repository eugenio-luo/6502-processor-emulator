#include "test.h"
#include "test_cpu.h"
#include "test_op.h"
#include "cpu/registers.h"

static int error_state = 0;

static void test_cpu(void);
static void test_op(void);

void
test_sys(void)
{
        test_cpu();
        test_op();
}

static void
test_cpu(void)
{
        test_cpu_regs();
        test_cpu_mem();
        test_cpu_stack();
}

static void
test_op(void)
{
        test_op_load();
        test_op_transfer();
        test_op_stack();
        test_op_shift();
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
