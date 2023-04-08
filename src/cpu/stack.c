#include <stdint.h>

#include "cpu/stack.h"
#include "log.h"
#include "cpu/registers.h"
#include "cpu/memory.h"

#define STACK_SIZE     0x100
#define STACK_OFFSET   0x100

#define STACK_PREV(SP)   (SP + 1) % STACK_SIZE
#define STACK_NEXT(SP)   (SP - 1) % STACK_SIZE

static uint8_t
stack_prev(uint8_t sp)
{
        uint8_t new_sp = (sp + 1) % STACK_SIZE;
        if (new_sp < sp)
                log_warning("[stack.c: stack_push] stack overflow");

        return new_sp;
}

static uint8_t
stack_next(uint8_t sp)
{
        uint8_t new_sp = (sp - 1) % STACK_SIZE;
        if (new_sp > sp)
                log_warning("[stack.c: stack_pop] stack underflow");

        return new_sp;
}

uint8_t
stack_top(void)
{
        return mem_get(STACK_OFFSET + stack_prev(reg_get_sp()));
}

void
stack_push(uint8_t val)
{
        uint8_t sp = reg_get_sp();
        mem_set(STACK_OFFSET + sp, val);

        reg_set_sp(stack_next(sp));
}

void
stack_pop(void)
{
        reg_set_sp(stack_prev(reg_get_sp()));
}
