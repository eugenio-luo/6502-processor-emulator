#include "system.h"

#ifdef TEST

#include "test.h"

#endif

int
main(int argc, char **argv)
{
        (void) argc, (void) argv;
        
        sys_init();

#ifdef TEST

        test_sys();

#endif
        /* sys_load() */
        
        /* sys_emu() */

        sys_quit();
        
        return 0;
}
