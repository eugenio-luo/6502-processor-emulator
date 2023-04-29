#ifndef NES_ROM_H
#define NES_ROM_H

#include "cpu/cpu.h"

#define HEADER_SIZE    16
#define TRAINER_SIZE   512
#define PRG_ROM_UNIT   0x4000

typedef struct {
        int valid;
        char *buf;
        int prg_rom;
        int vrom;
        int vertical_mir;
        int battery_ram;
        int trainer;
        int fscr_mir;
        int map_num;
        int ram;
        long size;
} rbuf_t;

void rom_load(const char *rom_path);
void rom_reset(void);
void rom_quit(void);

uint8_t rom_mem_get(addr_t addr);
void rom_mem_set(addr_t addr, uint8_t val);

/* used only for testing purpose */
rbuf_t *rom_get_rbuf(void);

#endif
