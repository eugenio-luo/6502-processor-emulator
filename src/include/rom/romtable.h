#ifndef NES_ROMTABLE_H
#define NES_ROMTABLE_H

#include <stdint.h>

#include "rom/rom.h"
#include "cpu/cpu.h"

enum {
        NROM = 0,
};

typedef uint8_t (*rom_mem_get_t)(rbuf_t *, addr_t);
typedef void (*rom_mem_set_t)(rbuf_t *, addr_t, uint8_t);

typedef struct {
        rom_mem_get_t get;
        rom_mem_set_t set;
} rom_map_t;

rom_map_t *rom_map_get(int map_num);

#endif
