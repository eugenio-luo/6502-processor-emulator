#include "opcode/opfunc.h"
#include "opcode/addr_mode.h"
#include "cpu/registers.h"

static int
op_branch_instr(addr_t addr, reg_flag_t flag, int is_set)
{
        int ret = op_get_page_cross();
        
        if ((~is_set ^ reg_is_flag_set(flag)) & 0x1) {
                reg_set_pc(addr);
                ++ret; 
        }

        return ret;
}
        
int
op_bcc(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        addr_t addr = op_get_addr(addr_mode, a, b);
        return op_branch_instr(addr, CARRY_FLAG, 0);
}

int
op_bcs(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        addr_t addr = op_get_addr(addr_mode, a, b);
        return op_branch_instr(addr, CARRY_FLAG, 1);
}

int
op_beq(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        addr_t addr = op_get_addr(addr_mode, a, b);
        return op_branch_instr(addr, ZERO_FLAG, 1);
}

int
op_bmi(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        addr_t addr = op_get_addr(addr_mode, a, b);
        return op_branch_instr(addr, NEG_FLAG, 1);
}

int
op_bne(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        addr_t addr = op_get_addr(addr_mode, a, b);
        return op_branch_instr(addr, ZERO_FLAG, 0);
}

int
op_bpl(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        addr_t addr = op_get_addr(addr_mode, a, b);
        return op_branch_instr(addr, NEG_FLAG, 0);
}

