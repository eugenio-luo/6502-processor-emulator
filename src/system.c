#include "system.h"
#include "log.h"

void
sys_init(void)
{
        log_init(LOG_DIR_PATH);

        log_write("[system.c: sys_init] system initialization...");
}

void
sys_reset(void)
{
        
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
