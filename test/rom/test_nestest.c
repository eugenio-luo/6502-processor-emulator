#include "test_rom.h"
#include "test_check.h"
#include "system.h"
#include "cpu/cpu.h"
#include "cpu/registers.h"
#include "cpu/memory.h"
#include "opcode/opcode.h"

void
test_nestest(void)
{
        int cycles = 7;
        reg_set_pc(0xC000);
        reg_clear_flags(0x10);
        sys_load("nestest.nes");

        log_write("02h:%03x CYC:%d ", mem_get(0x2), cycles);
        reg_log();
        for (;;) {
                cycles += op_next();
                log_write("02h:%03x CYC:%d ", mem_get(0x2), cycles);
                reg_log();
        }
}
