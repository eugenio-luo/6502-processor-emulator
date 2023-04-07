#ifndef NES_CPU_H
#define NES_CPU_H

#include <stdint.h>

typedef uint16_t addr_t;

#define HARD_RESET   1
#define SOFT_RESET   0

void cpu_init(void);

#endif
