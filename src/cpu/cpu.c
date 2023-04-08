#include "cpu/cpu.h"
#include "log.h"
#include "cpu/registers.h"
#include "cpu/memory.h"

void
cpu_init(void)
{
        log_write("[cpu.c: cpu_init] CPU initialization...");
        
        regs_init();
        mem_init();
}

void
cpu_reset(int hard)
{
        regs_reset(hard);
        mem_reset(hard);
}
