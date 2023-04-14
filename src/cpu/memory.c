#include <stdint.h>
#include <string.h>

#include "cpu/memory.h"
#include "cpu/cpu.h"
#include "log.h"

/* TODO:
   - handle CARTRIDGE_ADDR addresses
   - handle CPU_TEST addresses
   - handle APU_IO addresses
   - handle PPU addresses
*/

#define PPU_ADDR          0x2000
#define PPU_ADDR_SIZE     0x8
#define PPU_MIRROR_ADDR   0x2008

#define CPU_TEST_ADDR     0x4018

#define CARTR_ADDR        0x4020

typedef uint8_t (*getter_t)(addr_t);
typedef void (*setter_t)(addr_t, uint8_t);

static uint8_t memory[RAM_SIZE];

void
mem_init(void)
{
        log_write("[memory.c: mem_init] memory initialization...");

        mem_reset(HARD_RESET);
}

void
mem_reset(int hard)
{
        if (hard) {

                log_write("[memory.c: mem_reset] memory hard reset");

                memset(&memory[0], 0, RAM_SIZE);
        }
}

static uint8_t
mem_get_cartr(addr_t addr)
{
        log_error("[memory.c: mem_get] %x: CARTRIDGE_ADDR not implemented yet", addr);
        return -1;
}

static uint8_t
mem_get_cpu_test(addr_t addr)
{
        log_error("[memory.c: mem_get] %x: CPU_TEST_ADDR not implemented yet", addr);
        return -1;
}

static uint8_t
mem_get_apu_io(addr_t addr)
{
        log_error("[memory.c: mem_get] %x: APU_IO_ADDR not implemented yet", addr);
        return -1;
}

static uint8_t
mem_get_ppu(addr_t addr)
{
        addr_t real_addr = addr; 
        if (addr >= PPU_MIRROR_ADDR)
                real_addr = (addr - PPU_MIRROR_ADDR) % PPU_ADDR_SIZE + PPU_ADDR;
        
        log_error("[memory.c: mem_get] %x (%x): PPU_ADDR not implemented yet",
                  addr, real_addr);
        return -1;
}

static uint8_t
mem_get_ram(addr_t addr)
{
        addr_t real_addr = addr;
        if (addr >= RAM_MIRROR_ADDR)
                real_addr = (addr - RAM_MIRROR_ADDR) % RAM_SIZE;

        return memory[real_addr];
}

static uint8_t
mem_get_filter(addr_t addr)
{
        if (addr >= CARTR_ADDR)
                return mem_get_cartr(addr);

        if (addr >= CPU_TEST_ADDR)
                return mem_get_cpu_test(addr);

        return mem_get_apu_io(addr);
}

static const getter_t mem_getters[] = {
        mem_get_ram, mem_get_ram,     /* 0x0000 - 0x1FFF */
        mem_get_ppu, mem_get_ppu,     /* 0x2000 - 0x3FFF */
        mem_get_filter,               /* 0x4000 - 0x4FFF */
        mem_get_cartr, mem_get_cartr, /* 0x5000 - 0x6FFF */
        mem_get_cartr, mem_get_cartr, /* 0x7000 - 0x8FFF */
        mem_get_cartr, mem_get_cartr, /* 0x9000 - 0xAFFF */
        mem_get_cartr, mem_get_cartr, /* 0xB000 - 0xCFFF */
        mem_get_cartr, mem_get_cartr, /* 0xD000 - 0xEFFF */
        mem_get_cartr,                /* 0xF000 - 0xFFFF */
};

uint8_t
mem_get(addr_t addr)
{
        int idx = (addr & 0xF000) >> 12;
        getter_t getter = mem_getters[idx];
        return getter(addr);
}

static void
mem_set_cartr(addr_t addr, uint8_t val)
{
        log_error("[memory.c: mem_set] %x: CARTRIDGE_ADDR not implemented yet", addr);
        (void) val;
}

static void
mem_set_cpu_test(addr_t addr, uint8_t val)
{
        log_error("[memory.c: mem_set] %x: CPU_TEST_ADDR not implemented yet", addr);
        (void) val;
}

static void
mem_set_apu_io(addr_t addr, uint8_t val)
{
        log_error("[memory.c: mem_set] %x: APU_IO_ADDR not implemented yet", addr);
        (void) val;
}

static void
mem_set_ppu(addr_t addr, uint8_t val)
{
        addr_t real_addr = addr; 
        if (addr >= PPU_MIRROR_ADDR)
                real_addr = (addr - PPU_MIRROR_ADDR) % PPU_ADDR_SIZE + PPU_ADDR;
        
        log_error("[memory.c: mem_set] %x (%x): PPU_ADDR not implemented yet",
                  addr, real_addr);
        (void) val;
}

static void
mem_set_ram(addr_t addr, uint8_t val)
{
        addr_t real_addr = addr;
        if (addr >= RAM_MIRROR_ADDR)
                real_addr = (addr - RAM_MIRROR_ADDR) % RAM_SIZE;

        memory[real_addr] = val;
}

static void
mem_set_filter(addr_t addr, uint8_t val)
{
        if (addr >= CARTR_ADDR)
                mem_set_cartr(addr, val);

        if (addr >= CPU_TEST_ADDR)
                mem_set_cpu_test(addr, val);

        mem_set_apu_io(addr, val);
}

static const setter_t mem_setters[] = {
        mem_set_ram, mem_set_ram,     /* 0x0000 - 0x1FFF */
        mem_set_ppu, mem_set_ppu,     /* 0x2000 - 0x3FFF */
        mem_set_filter,               /* 0x4000 - 0x4FFF */
        mem_set_cartr, mem_set_cartr, /* 0x5000 - 0x6FFF */
        mem_set_cartr, mem_set_cartr, /* 0x7000 - 0x8FFF */
        mem_set_cartr, mem_set_cartr, /* 0x9000 - 0xAFFF */
        mem_set_cartr, mem_set_cartr, /* 0xB000 - 0xCFFF */
        mem_set_cartr, mem_set_cartr, /* 0xD000 - 0xEFFF */
        mem_set_cartr,                /* 0xF000 - 0xFFFF */
};

void
mem_set(addr_t addr, uint8_t val)
{
        int idx = (addr & 0xF000) >> 12;
        setter_t setter = mem_setters[idx];
        setter(addr, val);
}