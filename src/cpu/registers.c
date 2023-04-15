#include <stdint.h>

#include "cpu/registers.h"
#include "cpu/cpu.h"
#include "log.h"

/* TODO:
   - implement the B flags
*/

#define RESET_STACK_DEC  3

typedef struct {
        uint16_t pc; /* program counter */
        uint8_t sp; /* stack pointer */
        uint8_t acc; /* accumulator */
        uint8_t x;
        uint8_t y;
        uint8_t flags;
} regs_t;

static regs_t regs;

void
regs_init(void)
{
        log_write("[registers.c: regs_init] registers initialization...");
        
        regs_reset(HARD_RESET);
}

void
regs_reset(int hard)
{
        if (hard) {
                
                log_write("[registers.c: regs_reset] registers hard reset");
                
                reg_force_flags(INT_DISABLE | BREAK_COM0 | BREAK_COM1);

                reg_set_acc(0);
                reg_set_x(0);
                reg_set_y(0);

                reg_set_sp(INIT_STACK_PTR);

        } else {

                log_write("[registers.c: regs_reset] registers soft reset");

                reg_set_flags(INT_DISABLE);
                reg_set_sp(reg_get_sp() - RESET_STACK_DEC);
        }
}

void
reg_set_pc(uint16_t val)
{
        regs.pc = val;
}

void
reg_set_sp(uint8_t val)
{
        regs.sp = val;
}

void
reg_set_acc(uint8_t val)
{
        regs.acc = val;
}

void
reg_set_x(uint8_t val)
{
        regs.x = val;
}

void
reg_set_y(uint8_t val)
{
        regs.y = val;
}

void
reg_set_flags(reg_flag_t val)
{
        regs.flags |= val;
}

void
reg_force_flags(reg_flag_t val)
{
        regs.flags = val;
}

void
reg_clear_flags(reg_flag_t val)
{
        regs.flags &= ~val;
}

uint16_t
reg_get_pc(void)
{
        return regs.pc;
}

uint8_t
reg_get_sp(void)
{
        return regs.sp;
}

uint8_t
reg_get_acc(void)
{
        return regs.acc;
}

uint8_t
reg_get_x(void)
{
        return regs.x;
}

uint8_t
reg_get_y(void)
{
        return regs.y;
}

uint8_t
reg_get_flags(void)
{
        return regs.flags;
}

int
reg_is_flag_set(reg_flag_t val)
{
        return (regs.flags & val) ? 1 : 0;
}

void
reg_inc_pc(void)
{
        ++regs.pc;
}
