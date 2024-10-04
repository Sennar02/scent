#include <stdio.h>

#include "memory.hpp"

using namespace gr;

static const Array<i32, 5> ARRAY =
     {1, 2, 3, 4, 5};

int
main()
{
    Arena arena = arena_init(WIDTH_I32, 16, 4.0f);

    Slice<const i32> slice = slice_init<const i32>(&arena, 17);

    printf("slice:\n");
    for ( isize i = 1; i <= slice.items; i += 1 )
        printf("%2lli. %i\n", i, slice[i]);

    printf("\narray:\n");
    for ( isize i = 1; i <= ARRAY.items; i += 1 )
        printf("%2lli. %i\n", i, ARRAY[i]);

    slice = slice_from(&ARRAY);

    arena_reset(&arena);
    slice_clear(&slice);

    printf("\nslice:\n");
    for ( isize i = 1; i <= slice.items; i += 1 )
        printf("%2lli. %i\n", i, slice[i]);

    arena_drop(&arena);
}
