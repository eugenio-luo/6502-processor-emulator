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
                log_error("[main.c: main] A ROM file has to provided as argument");

#endif
        
        sys_init();

#ifdef TEST

        (void) argc, (void) argv;
        test_sys();
        
#else

        sys_load(argv[1]); 
        /* sys_emu() */

#endif
                
        sys_quit();
        
        return 0;
}
