#include <stdlib.h>

#include "system.h"
#include "log.h"

#ifdef TEST

#include "test.h"

#endif

int
main(int argc, char **argv)
{
#ifndef TEST

        if (argc < 2)
                log_error("[main.c: main] A ROM file has to provided as argument\n");

#endif
        
        sys_init();

#ifdef TEST

        (void) argc, (void) argv;
        test_sys();
        
#else

        sys_load(argv[1]); 

        int mem_start = 0;
        int obj_cycles = -1;

        if (argc > 3)
                mem_start = (int) strtol(argv[3], NULL, 0);
        if (argc > 2)
                obj_cycles = atoi(argv[2]);
        
        sys_emu(mem_start, obj_cycles);

#endif
                
        sys_quit();
        
        return 0;
}
