#ifndef GR_CORE_MEMORY_HPP
#define GR_CORE_MEMORY_HPP

#include "assert.hpp"
#include "types.hpp"
#include "arena.hpp"

namespace gr
{
    template <class Val>
    Val*
    arena_alloc_type(Arena* self, isize count)
    {
        static const isize size = sizeof(Val);
        static const isize algn = alignof(Val);

        return (Val*) arena_alloc(self, algn, size, count);
    }
} // namespace gr

#endif // GR_CORE_MEMORY_HPP
