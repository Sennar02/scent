#include <stdio.h>

#include "memory.hpp"

using namespace gr;

int
main()
{
    Arena arena = arena_init(64);
    i32*  block = (i32*) arena_alloc(&arena, alignof(i32), sizeof(i32), 4);

    if ( block == 0 ) return 1;

    for ( i32 i = 0; i < 4; i += 1 )
        printf("%p\n", block + i);
}
