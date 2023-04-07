#include "system.h"
#include "log.h"
#include "cpu/registers.h"
#include "cpu/memory.h"

void
sys_init(void)
{
        log_init(LOG_DIR_PATH);

        log_write("[system.c: sys_init] system initialization...");

        regs_init();
        mem_init();
}

void
sys_reset(int hard)
{
        regs_reset(hard);
        mem_reset(hard);
}        

void
sys_quit(void)
{
        log_write("[system.c: sys_quit] system termination...");
        
        log_quit();
}

void
sys_emu(void)
{
        
}        
