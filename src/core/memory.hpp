#ifndef GR_CORE_MEMORY_HPP
#define GR_CORE_MEMORY_HPP

#include "assert.hpp"
#include "types.hpp"
#include "arena.hpp"

namespace gr
{
    template <class Val>
    Val*
    arena_alloc_of(Arena* arena, isize count);
} // namespace gr

#include "memory.inl"

#endif // GR_CORE_MEMORY_HPP
