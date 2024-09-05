#ifndef SCENT_COLOUR_HPP
#define SCENT_COLOUR_HPP

#include "types.hpp"
#include "vec4.hpp"

namespace scent
{
    using Colour = Vec4<u8>;

    static const Colour COLOUR_WHITE = {0xffu, 0xffu, 0xffu, 0xffu};
    static const Colour COLOUR_BLACK = { 0x00,  0x00,  0x00, 0xffu};
} // scent

#endif // SCENT_COLOUR_HPP
