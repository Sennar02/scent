#include <stdio.h>
#include <malloc.h>

#include "utils.hpp"
#include "robin_map.hpp"
#include "arena_alloc.hpp"

using namespace scent;

int
main()
{
    u32   size = 1024u;
    void* pntr = malloc(size);

    Arena_Alloc arena = {pntr, size};

    Robin_Map<i8, u32> mappa = {arena, 10u};

    for ( u32 i = 0; i < 20u; i += 1u )
        mappa.insert('0' + i, i);

    for ( u32 i = 0; i < size; i += 1u ) {
        printf("%3hhu ", ((i8*) pntr)[i]);

        if ( (i + 1) % 16u == 0 )
            printf("\n");
    }

    mappa['1'].val() = 3;

    auto key = mappa.keys();
    auto val = mappa.values();

    for ( u32 i = 0; i < key.size(); i += 1u )
        printf("%c -> %u\n", key[i], val[i]);

    free(pntr);
}
