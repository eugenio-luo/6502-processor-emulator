#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "rom/rom.h"
#include "log.h"

/* TODO: for now it only supports iNES files, UNIF files should be implemented */

#define HEAD_CONST           "NES\x1A"
#define HEAD_CONST_SIZE      4
#define PRG_ROM_BYTE         4
#define VROM_BYTE            5

#define ROM_CTRL_BYTE1       6
enum {
        MIRROR_BIT = (1 << 0),
        BATTERY_BIT = (1 << 1),
        TRAINER_BIT = (1 << 2),
        FSCR_BIT = (1 << 3),

        MAP_NUM_LBITS = (1 << 4),
};

#define ROM_CTRL_BYTE2         7
#define MAP_NUM_HBITS_MASK     0xF0

#define RAM_BYTE               8

struct {
        char *buf;
        int prg_rom;
        int vrom;
        int vertical_mir;
        int battery_ram;
        int trainer;
        int fscr_mir;
        int map_num;
        int ram;
        long size;
} rbuf;

static void
rom_read_header(void)
{
        for (int i = 0; i < HEAD_CONST_SIZE; ++i) {
                if (rbuf.buf[i] != HEAD_CONST[i])
                        log_error("[rom.c: rom_load] missing NES header in file");
        }
        
        rbuf.prg_rom = rbuf.buf[PRG_ROM_BYTE];
        log_write("16KB PRG-ROM banks: %d", rbuf.prg_rom);

        rbuf.vrom = rbuf.buf[VROM_BYTE];
        log_write("8KB VROM banks: %d", rbuf.vrom);
        
        rbuf.vertical_mir = (rbuf.buf[ROM_CTRL_BYTE1] & MIRROR_BIT) ? 1 : 0;
        log_write("vertical mirroring: %s", (rbuf.vertical_mir) ? "yes" : "no");

        rbuf.battery_ram = (rbuf.buf[ROM_CTRL_BYTE1] & BATTERY_BIT) ? 1 : 0;
        log_write("battery-backed RAM: %s", (rbuf.battery_ram) ? "yes" : "no");

        rbuf.trainer = (rbuf.buf[ROM_CTRL_BYTE1] & TRAINER_BIT) ? 1 : 0;
        log_write("512-byte trainer: %s", (rbuf.trainer) ? "yes" : "no");

        rbuf.fscr_mir = (rbuf.buf[ROM_CTRL_BYTE1] & FSCR_BIT) ? 1 : 0;
        log_write("4 screen mirroring: %s", (rbuf.fscr_mir) ? "yes" : "no");

        rbuf.map_num = rbuf.buf[ROM_CTRL_BYTE1] >> MAP_NUM_LBITS;
        rbuf.map_num |= rbuf.buf[ROM_CTRL_BYTE2] & MAP_NUM_HBITS_MASK;
        log_write("mapper number: %x", rbuf.map_num);

        rbuf.ram = rbuf.buf[RAM_BYTE];
        log_write("8k RAM banks: %d", rbuf.ram);
}

static void
rom_file_to_buf(const char *rom_path)
{
        FILE *f_ptr = fopen(rom_path, "r");

        if (!f_ptr)
                log_error("[rom.c: rom_load] fopen failed: %s", strerror(errno));

        if (fseek(f_ptr, 0L, SEEK_END))
                log_error("[rom.c: rom_load] fseek failed");

        long f_size = ftell(f_ptr);

        if (f_size == -1)
                log_error("[rom.c: rom_load] file size error: %d", f_size);

        if (fseek(f_ptr, 0L, SEEK_SET))
                log_error("[rom.c: rom_load] fseek failed");

        rbuf.buf = malloc(f_size);
        long r_size = fread(rbuf.buf, sizeof(uint8_t), f_size, f_ptr);
        rbuf.size = f_size;

        if (r_size != f_size)
                log_error("[rom.c: rom_load] read size different from file size");
        
        if (ferror(f_ptr))
                log_error("[rom.c: rom_load] error in reading file");

        fclose(f_ptr);
}

void
rom_load(const char *rom_path)
{
        rom_file_to_buf(rom_path);
        rom_read_header();
}

void
rom_quit(void)
{
        if (rbuf.buf)
                free(rbuf.buf);
}
