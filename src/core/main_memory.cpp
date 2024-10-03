#include <stdio.h>

#include "memory.hpp"

using namespace gr;

int
main()
{
    Arena arena = arena_init(64, ARENA_GROWTH_BASE);
    i32*  block = arena_alloc_of<i32>(&arena, 100);

    if ( block == 0 ) return 1;

    printf("0x%llx\n", (usize) block);

    arena_drop(&arena);
}
