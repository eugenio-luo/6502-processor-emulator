#include "opcode/addr_mode.h"
#include "log.h"
#include "cpu/memory.h"
#include "cpu/registers.h"
#include "opcode/optable.h"

typedef addr_t (*addr_func_t)(uint8_t a, uint8_t b);

#define ZERO_PAGE_SIZE   0x100

static int is_page_crossed = 0;

static inline void
check_page_cross(addr_t addr, uint8_t val)
{
        if (((addr + val) >> 8) ^ (addr >> 8))
                is_page_crossed = 1;
}

int
op_get_page_cross(void)
{
        return is_page_crossed;
}

static addr_t
addr_mode_error(uint8_t a, uint8_t b)
{
        (void) a, (void) b;
        log_error("[addr_mode.c: addr_mode_error] inexistant address mode");
        return -1;
}

static addr_t
addr_mode_zero(uint8_t a, uint8_t b)
{
        (void) b;
        return a; 
}

static addr_t
addr_mode_zerox(uint8_t a, uint8_t b)
{
        (void) b;
        uint8_t x = reg_get_x();

        return (a + x) % ZERO_PAGE_SIZE;
}

static addr_t
addr_mode_zeroy(uint8_t a, uint8_t b)
{
        (void) b;
        uint8_t y = reg_get_y();

        return (a + y) % ZERO_PAGE_SIZE;
}

static addr_t
addr_mode_rel(uint8_t a, uint8_t b)
{
        (void) b;
        addr_t pc = reg_get_pc();
        
        check_page_cross(pc, a);
        
        return pc + a;
}

static addr_t
addr_mode_abs(uint8_t a, uint8_t b)
{
        return (b << 8) | a;
}

static addr_t
addr_mode_absx(uint8_t a, uint8_t b)
{
        addr_t addr = (b << 8) | a;
        uint8_t x = reg_get_x();

        check_page_cross(addr, x);
       
        return addr + x;
}

static addr_t
addr_mode_absy(uint8_t a, uint8_t b)
{
        addr_t addr = (b << 8) | a;
        uint8_t y = reg_get_y();

        check_page_cross(addr, y);
        
        return ((b << 8) | a) + y;
}

static addr_t
addr_mode_indr(uint8_t a, uint8_t b)
{
        addr_t addr = (b << 8) | a;

        uint8_t val0 = mem_get(addr);
        uint8_t val1 = mem_get(addr + 1);

        return (val1 << 8) | val0;
}

static addr_t
addr_mode_indx_indr(uint8_t a, uint8_t b)
{
        addr_t addr = addr_mode_zerox(a, b);
        
        uint8_t val0 = mem_get(addr);
        uint8_t val1 = mem_get(addr + 1);

        return (val1 << 8) | val0;
}

static addr_t
addr_mode_indr_indy(uint8_t a, uint8_t b)
{
        (void) b;
        uint8_t y = reg_get_y();
        uint8_t val0 = mem_get(a);
        uint8_t val1 = mem_get(a + 1);
        addr_t addr = (val1 << 8) | val0;

        check_page_cross(addr, y);

        return addr + y;
}

static addr_func_t addr_mode_table[] = {
        addr_mode_error,
        addr_mode_error,
        addr_mode_error,
        addr_mode_zero,
        addr_mode_zerox,
        addr_mode_zeroy,
        addr_mode_rel,
        addr_mode_abs,
        addr_mode_absx,
        addr_mode_absy,
        addr_mode_indr,
        addr_mode_indx_indr,
        addr_mode_indr_indy,
};

addr_t
op_get_addr(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        is_page_crossed = 0;
        
        addr_func_t addr_func = addr_mode_table[addr_mode];
        return addr_func(a, b);
}

uint8_t
op_get_addr_val(addr_mode_t addr_mode, uint8_t a, uint8_t b)
{
        switch (addr_mode) {
        case ACC:
                is_page_crossed = 0;
                return reg_get_acc();

        case IMM:
                is_page_crossed = 0;
                return a;
                
        default:
                return mem_get(op_get_addr(addr_mode, a, b));
        }
}

void
op_set_addr_val(addr_mode_t addr_mode, uint8_t a, uint8_t b, uint8_t val)
{
        if (addr_mode == ACC) {
                is_page_crossed = 0;
                reg_set_acc(val);
                return;
        }
        
        mem_set(op_get_addr(addr_mode, a, b), val);
}
