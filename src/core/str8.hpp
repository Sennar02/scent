#ifndef GR_CORE_STR8_HPP
#define GR_CORE_STR8_HPP

#include <core/types.hpp>

namespace gr
{
    struct Str8 {
        //
        //
        //
        const byte* data = 0;

        //
        //
        //
        isize items = 0;

        //
        //
        //
        Str8() = default;

        //
        //
        //
        template <isize Len>
        constexpr Str8(const byte (&seq)[Len]);

        //
        //
        //
        const byte&
        operator[](isize index) const;
    };

    static const isize WIDTH_STR = gr_type_width(Str8);
    static const isize ALIGN_STR = gr_type_align(Str8);

    //
    //
    // Implementation
    //
    //

    template <isize Len>
    constexpr Str8::Str8(const byte (&seq)[Len])
        : data {seq}
        , items {Len - 1}
    {}
} // namespace gr

#endif // GR_CORE_STR8_HPP
