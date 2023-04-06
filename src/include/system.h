#ifndef NES_SYSTEM_H
#define NES_SYSTEM_H

void sys_init(void);
void sys_reset(void);
void sys_quit(void);
void sys_load(const char *rom_path);
void sys_emu(void);

#endif
