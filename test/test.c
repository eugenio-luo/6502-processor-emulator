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
        test_regs();
        test_mem();
        test_stack();
}

static void
test_op(void)
{
        test_load();
        test_transfer();
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
