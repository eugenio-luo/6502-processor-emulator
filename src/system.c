#include "system.h"
#include "log.h"
#include "cpu/cpu.h"
#include "rom/rom.h"

void
sys_init(void)
{
        log_init(LOG_DIR_PATH);

        log_write("[system.c: sys_init] system initialization...");

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
        log_write("[system.c: sys_quit] system termination...");
        
        log_quit();
        rom_quit();
}

void
sys_load(const char *rom_path)
{
        log_write("[system.c: sys_load] system loading " GREEN "%s" RESET "...",
                  rom_path);

        rom_load(rom_path);
}

void
sys_emu(void)
{
        
}        
