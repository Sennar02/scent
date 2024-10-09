#include <stdio.h>

#include <core/types.hpp>
#include <core/arena.hpp>
#include <core/slice.hpp>

using namespace gr;

int
main()
{
    Arena      arena = arena_init(WIDTH_I32, 16, 4.0f);
    Slice<i32> slice = {};
    Slice<i32> other = {};

    slice = slice_insert(&slice, &arena, 1, Array<i32>({1, 2, 3, 4, 5, 6, 7, 8}));
    other = slice_copy(&slice, &arena);

    slice = slice_resize(&slice, &arena, 16);

    gr_exec_expect(slice.data != other.data, "");

    printf("slice(%li/%li):\n", slice.items, slice.limit);
    for ( isize i = 1; i <= slice.items; i += 1 )
        printf("%2li. %i\n", i, slice[i]);

    printf("\nother(%li/%li):\n", other.items, other.limit);
    for ( isize i = 1; i <= other.items; i += 1 )
        printf("%2li. %i\n", i, other[i]);

    slice_pull(&slice, 2, 2);

    printf("\nslice(%li/%li):\n", slice.items, slice.limit);
    for ( isize i = 1; i <= slice.items; i += 1 )
        printf("%2li. %i\n", i, slice[i]);

    slice_empty(&slice);

    printf("\nslice(%li/%li):\n", slice.items, slice.limit);
    for ( isize i = 1; i <= slice.items; i += 1 )
        printf("%2li. %i\n", i, slice[i]);

    arena_drop(&arena);
}
