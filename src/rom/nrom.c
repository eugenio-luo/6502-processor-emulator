#include <stdint.h>

#include "rom/romfunc.h"
#include "rom/rom.h"
#include "cpu/cpu.h"

#define PRG_ROM_START    0x8000
#define MIRROR_START     0xC000

static inline int
nrom_get_idx(rbuf_t *rbuf, addr_t addr)
{
        addr_t real_addr = addr - PRG_ROM_START;

        if (addr >= MIRROR_START && rbuf->prg_rom == 1)
                real_addr -= PRG_ROM_UNIT;
        
        return real_addr + HEADER_SIZE + ((rbuf->trainer) ? TRAINER_SIZE : 0); 
}

uint8_t
rom_nrom_get(rbuf_t *rbuf, addr_t addr)
{
        int idx = nrom_get_idx(rbuf, addr);
        return rbuf->buf[idx];
}

void
rom_nrom_set(rbuf_t *rbuf, addr_t addr, uint8_t val)
{
        int idx = nrom_get_idx(rbuf, addr);
        rbuf->buf[idx] = val;
}
