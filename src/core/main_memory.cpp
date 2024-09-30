#include <stdio.h>

#include "memory.hpp"

using namespace core;

int
main()
{
    Region r = { 256 };

    int* pntr = (int*) r.require(100 * sizeof(int), alignof(int));

    printf("0x%lx\n", (uarch) pntr);
}
