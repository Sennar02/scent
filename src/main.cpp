#include <stdio.h>

#include "empty_alloc.hpp"
#include "arena_alloc.hpp"
#include "array_map.hpp"

using namespace scent;

int
main()
{
    Arena_Alloc arena = {1024};

    Array_Map<u32, i8> map = {arena, 5};

    map.insert(4, 'e');
    map.insert(0, 'a');
    map.insert(2, 'c');

    auto k = map.keys();
    auto v = map.values();

    for ( u32 i = 0; i < k.size(); i += 1 )
        printf("| %2u | %2c |\n", k[i], v[i]);
    printf("\n");

    for ( u32 i = 0; i < map._size; i += 1 ) {
        if ( map._indx[i] != 0 )
            printf("| %2u | ", map._indx[i]);
        else
            printf("| %2c | ", ' ');

        if ( i < map._count )
            printf("%2u | %2u | %2c |\n",
                map._hash[i], map._head[i], map._body[i]);
        else
            printf("%2c | %2c | %2c |\n",
                ' ', ' ', ' ');
    }
    printf("\n");

    map.remove(4);

    for ( u32 i = 0; i < map._size; i += 1 ) {
        if ( map._indx[i] != 0 )
            printf("| %2u | ", map._indx[i]);
        else
            printf("| %2c | ", ' ');

        if ( i < map._count )
            printf("%2u | %2u | %2c |\n",
                map._hash[i], map._head[i], map._body[i]);
        else
            printf("%2c | %2c | %2c |\n",
                ' ', ' ', ' ');
    }
    printf("\n");

    map.remove(2);

    for ( u32 i = 0; i < map._size; i += 1 ) {
        if ( map._indx[i] != 0 )
            printf("| %2u | ", map._indx[i]);
        else
            printf("| %2c | ", ' ');

        if ( i < map._count )
            printf("%2u | %2u | %2c |\n",
                map._hash[i], map._head[i], map._body[i]);
        else
            printf("%2c | %2c | %2c |\n",
                ' ', ' ', ' ');
    }
    printf("\n");

    map.remove(0);

    for ( u32 i = 0; i < map._size; i += 1 ) {
        if ( map._indx[i] != 0 )
            printf("| %2u | ", map._indx[i]);
        else
            printf("| %2c | ", ' ');

        if ( i < map._count )
            printf("%2u | %2u | %2c |\n",
                map._hash[i], map._head[i], map._body[i]);
        else
            printf("%2c | %2c | %2c |\n",
                ' ', ' ', ' ');
    }

    map.drop();

    k = map.keys();
    v = map.values();

    printf("\n");

    for ( u32 i = 0; i < k.size(); i += 1 )
        printf("| %2u | %2c |\n", k[i], v[i]);
}
