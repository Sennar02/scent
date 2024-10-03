#include <stdio.h>

#include "memory.hpp"

using namespace gr;

int
main()
{
    Arena arena = arena_init(SIZE_I32, 16, 0.0f);

    i32* block = (i32*)
        arena_alloc(&arena, ALIGN_I32, SIZE_I32, 17);

    if ( block == 0 ) return 1;

    printf("0x%llx\n", (usize) block);

    arena_drop(&arena);
}
