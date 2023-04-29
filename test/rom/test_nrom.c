#include "test_rom.h"
#include "test_check.h"
#include "system.h"
#include "cpu/cpu.h"
#include "cpu/memory.h"

void
test_rom_nrom(void)
{
        uint8_t val;
        sys_load("nestest.nes");
        
        /* 1. check if PRG-ROM read works */
        val = mem_get(0x8010);
        TEST_CHECK("nrom", 1, val == 0x20);
        
        /* 2. check if PRG-ROM write works */
        mem_set(0x8010, 0x40);
        val = mem_get(0x8010);
        TEST_CHECK("nrom", 2, val == 0x40);
        
        /* 1. check if PRG-ROM mirror read works */
        mem_set(0x8010, 0x80);
        val = mem_get(0xC010);
        TEST_CHECK("nrom", 3, val == 0x80);

        /* 2. check if PRG-ROM mirror write works */
        mem_set(0xC010, 0x44);
        val = mem_get(0x8010);
        TEST_CHECK("nrom", 4, val == 0x44);

        sys_reset(HARD_RESET);
}
