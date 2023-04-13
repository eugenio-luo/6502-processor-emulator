#ifndef NES_ADDR_MODE_H
#define NES_ADDR_MODE_H

#include <stdint.h>

#include "cpu/cpu.h"
#include "opcode/optable.h"

int op_get_page_cross(void);
addr_t op_get_addr(addr_mode_t addr_mode, uint8_t a, uint8_t b);
uint8_t op_get_addr_val(addr_mode_t addr_mode, uint8_t a, uint8_t b);

#endif
