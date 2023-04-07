#ifndef NES_MEMORY_H
#define NES_MEMORY_H

#include "cpu/cpu.h"

#define RAM_SIZE          0x800
#define RAM_MIRROR_ADDR   RAM_SIZE 
#define RAM_MIRROR_SIZE   (RAM_SIZE * 3)

void mem_init(void);
void mem_reset(int hard);

uint8_t mem_get(addr_t addr);
void mem_set(addr_t addr, uint8_t val);

#endif
