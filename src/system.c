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
}

void
sys_reset(void)
{
        regs_reset(SOFT_RESET);
        mem_reset();
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
