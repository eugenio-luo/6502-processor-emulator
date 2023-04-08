#include "system.h"
#include "log.h"
#include "cpu/cpu.h"

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
