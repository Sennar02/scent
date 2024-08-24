#include <stdio.h>
#include <malloc.h>

#include "arena_alloc.hpp"
#include "array_list.hpp"

using namespace scent;

int
main()
{
    Arena_Alloc alloc1 = {malloc(64), 64};
    Arena_Alloc alloc2 = {malloc(1024), 1024};

    Array_List<const char*> names = {alloc1, 2};

    names.insert(0, "giovanni");
    names.insert(1, "mattia");

    printf("names  = %p\n", (void*) names._pntr);
    printf("alloc1 = %u\n", alloc1.next(1));
    printf("alloc2 = %u\n", alloc2.next(1));

    for ( u32 i = 0; i < names._size; i += 1 )
        printf("%3u. '%s'\n", i, names._pntr[i]);

    printf("resize = %u\n", names.resize(alloc2, 10));

    printf("names  = %p\n", (void*) names._pntr);
    printf("alloc1 = %u\n", alloc1.next(1));
    printf("alloc2 = %u\n", alloc2.next(1));

    for ( u32 i = 0; i < names._size; i += 1 )
        printf("%3u. '%s'\n", i, names._pntr[i]);
}
