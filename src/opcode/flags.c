#include "opcode/opfunc.h"
#include "cpu/registers.h"

int
op_clc(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;
        
        reg_clear_flags(CARRY_FLAG);
        return 0;
}

int
op_cld(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;
        
        reg_clear_flags(DEC_MODE);
        return 0;
}

int
op_cli(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;
        
        reg_clear_flags(INT_DISABLE);
        return 0;
}

int
op_clv(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;
        
        reg_clear_flags(OVER_FLAG);
        return 0;
}

int
op_sec(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;
        
        reg_set_flags(CARRY_FLAG);
        return 0;
}

int
op_sed(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;
        
        reg_set_flags(DEC_MODE);
        return 0;
}

int
op_sei(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        (void) addr_mode, (void) a, (void) b;
        
        reg_set_flags(INT_DISABLE);
        return 0;
}
