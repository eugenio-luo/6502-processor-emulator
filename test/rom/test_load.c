#include "test_rom.h"
#include "test_check.h"
#include "system.h"
#include "rom/rom.h"
#include "cpu/cpu.h"

void
test_rom_load(void)
{
        /* 1 - 8. check if the loaded values are correct */
        sys_load("nestest.nes");
        rbuf_t *rbuf = rom_get_rbuf();

        TEST_CHECK("rom load", 1, rbuf->prg_rom == 1); 
        TEST_CHECK("rom load", 2, rbuf->vrom == 1);
        TEST_CHECK("rom load", 3, !rbuf->vertical_mir); 
        TEST_CHECK("rom load", 4, !rbuf->battery_ram); 
        TEST_CHECK("rom load", 5, !rbuf->trainer); 
        TEST_CHECK("rom load", 6, !rbuf->fscr_mir); 
        TEST_CHECK("rom load", 7, rbuf->map_num == 0); 
        TEST_CHECK("rom load", 8, rbuf->ram == 0); 

        sys_reset(HARD_RESET);
}
