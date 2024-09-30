#include "memory.hpp"

namespace core
{
    i8*
    align_forw(i8* pntr, u8 align)
    {
        RUNTIME_ASSERT(align != 0 && (align & (align - 1u)) == 0,
            "The alignment is not a power of two");

        uarch value = (uarch) pntr;
        uarch error = value & (align - 1u);

        error = (error != 0) * (align - error);

        return pntr + error;
    }
} // namespace core
