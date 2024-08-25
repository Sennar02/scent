#include <stdio.h>
#include <malloc.h>

#include "utils.hpp"
#include "arena_alloc.hpp"
#include "array_list.hpp"

using namespace scent;

int
main()
{
    Arena_Alloc alloc = {malloc(1024), 1024};

    Array_List<const char*> names = {alloc};

    printf("%u\n", names.insert(0, "giovanni"));
    printf("%u\n", names.insert(1, "mattia"));

    auto v = names.values();

    for ( u32 i = 0; i < v.size(); i += 1 )
        printf("%3u. '%s'\n", i, v[i]);
}
