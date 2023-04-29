#ifndef NES_OPCODE_H
#define NES_OPCODE_H

#include <stdint.h>

void op_init(void);
void op_reset(void);
uint8_t op_read_byte(void);
int op_next(void);
int op_exec(uint8_t op, uint8_t a, uint8_t b);

#endif
