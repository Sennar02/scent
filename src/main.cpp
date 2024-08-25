#include <stdio.h>
#include <malloc.h>

#include "utils.hpp"
#include "robin_map.hpp"
#include "arena_alloc.hpp"

using namespace scent;

int
main()
{
    Arena_Alloc alloc = {malloc(1024), 1024};

    Robin_Map<u32, const char*> names = {alloc, 10};

    printf("insert = %u\n", names.insert(7, "a"));
    printf("insert = %u\n", names.insert(6, "b"));
    printf("insert = %u\n", names.insert(5, "c"));

    for ( u32 i = 0; i < names._size; i += 1 ) {
        if ( i == 0 ) {
            printf("     | dist | indx | indx | head | body       |\n");
            printf("     + ---- + ---- + ---- + ---- + ---------- +\n");
        }

        printf("%3u. ", i);

        if ( names._ctrl[i].dist != 0 )
            printf("| %4u | %4u | ", names._ctrl[i].dist, names._ctrl[i].indx);
        else
            printf("|      |      | ");

        if ( i < names._count )
            printf("%4u | %4u | %10s |\n", names._indx[i], names._head[i], names._body[i]);
        else
            printf("     |      |            |\n");
    }

    printf("insert = %u\n", names.insert(15, "d"));

    for ( u32 i = 0; i < names._size; i += 1 ) {
        if ( i == 0 ) {
            printf("     | dist | indx | indx | head | body       |\n");
            printf("     + ---- + ---- + ---- + ---- + ---------- +\n");
        }

        printf("%3u. ", i);

        if ( names._ctrl[i].dist != 0 )
            printf("| %4u | %4u | ", names._ctrl[i].dist, names._ctrl[i].indx);
        else
            printf("|      |      | ");

        if ( i < names._count )
            printf("%4u | %4u | %10s |\n", names._indx[i], names._head[i], names._body[i]);
        else
            printf("     |      |            |\n");
    }

    auto k = names.keys();
    auto v = names.values();

    printf("values =\n");

    for ( u32 i = 0; i < v.size(); i += 1 )
        printf("%3u. '%s'\n", k[i], v[i]);

    names[5].val() = "z";

    printf("values =\n");

    for ( u32 i = 0; i < v.size(); i += 1 )
        printf("%3u. '%s'\n", k[i], v[i]);
}
