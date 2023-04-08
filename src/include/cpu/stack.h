#ifndef NES_STACK_H
#define NES_STACK_H

#include <stdint.h>

uint8_t stack_top(void);
void stack_push(uint8_t val);
void stack_pop(void);

#endif
