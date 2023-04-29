#include "opcode/opcode.h"
#include "log.h"
#include "opcode/optable.h"
#include "opcode/opfunc.h"
#include "cpu/memory.h"
#include "cpu/registers.h"

void
op_init(void)
{
        op_reset();
}

void
op_reset(void)
{
        
}

uint8_t
op_read_byte(void)
{
        uint8_t byte = mem_get(reg_get_pc());
        reg_inc_pc();
        return byte;
}

int
op_next(void)
{
        uint8_t b = op_read_byte();
        opcode_t *opcode = op_get(b);
        uint8_t args[2] = {0};

        for (int i = 0; i < opcode->args; ++i)
                args[i] = op_read_byte();
        
        return opcode->cycles + opcode->func(opcode->addr_mode, args[0], args[1]);
}

int
op_exec(uint8_t op, uint8_t a, uint8_t b)
{
        opcode_t *opcode = op_get(op);

        return opcode->cycles + opcode->func(opcode->addr_mode, a, b);

}
