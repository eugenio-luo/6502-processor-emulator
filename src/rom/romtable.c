#include "rom/romtable.h"
#include "rom/romfunc.h"

static rom_map_t rom_maps[] = {
        [NROM] = {rom_nrom_get, rom_nrom_set},
};

rom_map_t *
rom_map_get(int map_num)
{
        return &rom_maps[map_num];
}
