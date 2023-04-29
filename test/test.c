#include "test.h"
#include "test_cpu.h"
#include "test_op.h"
#include "test_rom.h"
#include "cpu/registers.h"

static int error_state = 0;

static void test_cpu(void);
static void test_op(void);
static void test_rom(void);

void
test_sys(void)
{
        test_cpu();
        test_op();
        test_rom();
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
        test_op_logic();
        test_op_arith();
        test_op_incdec();
        test_op_branch();
        test_op_flags();
        test_op_control();
}

static void
test_rom(void)
{
        test_rom_load();
        test_rom_nrom();

        test_nestest();
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
