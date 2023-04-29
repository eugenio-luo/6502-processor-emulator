#ifndef NES_ROMFUNC_H
#define NES_ROMFUNC_H

#include "rom/rom.h"
#include "cpu/cpu.h"

#define ROM_GET_FUNC_DECL(NAME) uint8_t NAME(rbuf_t *rbuf, addr_t addr)
#define ROM_SET_FUNC_DECL(NAME) void NAME(rbuf_t *rbuf, addr_t addr, uint8_t val)

ROM_GET_FUNC_DECL(rom_nrom_get);
ROM_SET_FUNC_DECL(rom_nrom_set);

#endif
