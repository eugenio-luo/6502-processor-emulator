#include "test_rom.h"
#include "test_check.h"
#include "system.h"
#include "cpu/cpu.h"
#include "cpu/registers.h"
#include "opcode/opcode.h"

void
test_nestest(void)
{
        int cycles = 7;
        reg_set_pc(0xC000);
        sys_load("nestest.nes");

        log_write("CYC:%d ", cycles);
        reg_log();
        for (;;) {
                cycles += op_next();
                log_write("CYC:%d ", cycles);
                reg_log();
        }
}
