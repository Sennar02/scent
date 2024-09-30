#ifndef CORE_MEMORY_HPP
#define CORE_MEMORY_HPP

#include "assert.hpp"
#include "types.hpp"
#include "buffer.hpp"
#include "region.hpp"

namespace core
{
    i8*
    align_forw(i8* pntr, u8 align);
} // namespace core

#endif // CORE_MEMORY_HPP
