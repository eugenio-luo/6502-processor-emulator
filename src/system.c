#include "system.h"
#include "log.h"
#include "cpu/cpu.h"
#include "rom/rom.h"
#include "cpu/memory.h"
#include "cpu/registers.h"
#include "opcode/opcode.h"

void
sys_init(void)
{
        log_init(LOG_DIR_PATH);

        log_write("[system.c: sys_init] system initialization...\n");

        cpu_init();
}

void
sys_reset(int hard)
{
        cpu_reset(hard);
        rom_reset();
}        

void
sys_quit(void)
{
        log_write("[system.c: sys_quit] system termination...\n");
        
        log_quit();
        rom_quit();
}

void
sys_load(const char *rom_path)
{
        log_write("[system.c: sys_load] system loading " GREEN "%s" RESET "...\n",
                  rom_path);

        rom_load(rom_path);
}

void
sys_emu(int mem_start, int obj_cycles)
{
        if (mem_start)
                reg_set_pc(mem_start);
        int cycles = 0;
        log_write("02h:%03x CYC:%d ", mem_get(0x2), cycles);
        reg_log();

        while (obj_cycles == -1 || cycles < obj_cycles) {

                cycles += op_next();
                log_write("02h:%03x CYC:%d ", mem_get(0x2), cycles);
                reg_log();
        }
}        
