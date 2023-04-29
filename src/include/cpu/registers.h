#ifndef NES_REGISTERS_H
#define NES_REGISTERS_H

#include <stdint.h>

#define INIT_STACK_PTR   0xFD

typedef enum {
        CARRY_FLAG   = (1 << 0),
        ZERO_FLAG    = (1 << 1),
        INT_DISABLE  = (1 << 2),
        DEC_MODE     = (1 << 3),
        BREAK_COM0   = (1 << 4),
        BREAK_COM1   = (1 << 5),
        OVER_FLAG    = (1 << 6),
        NEG_FLAG     = (1 << 7),
        ALL_FLAG     = 0xFF,
} reg_flag_t;

void regs_init(void);
void regs_reset(int hard);

void reg_set_pc(uint16_t val);
void reg_set_sp(uint8_t val);
void reg_set_acc(uint8_t val);
void reg_set_x(uint8_t val);
void reg_set_y(uint8_t val);
void reg_set_flags(reg_flag_t val);
void reg_force_flags(reg_flag_t val);
void reg_clear_flags(reg_flag_t val);

uint16_t reg_get_pc(void);
uint8_t reg_get_sp(void);
uint8_t reg_get_acc(void);
uint8_t reg_get_x(void);
uint8_t reg_get_y(void);
uint8_t reg_get_flags(void);
int reg_is_flag_set(reg_flag_t val);

void reg_inc_pc(void);
void reg_inc_x(void);
void reg_inc_y(void);

void reg_dec_x(void);
void reg_dec_y(void);

void reg_log(void);

#endif
