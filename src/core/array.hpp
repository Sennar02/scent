#ifndef GR_CORE_ARRAY_HPP
#define GR_CORE_ARRAY_HPP

#include <core/types.hpp>

namespace gr
{
    template <class Val>
    struct Array {
        //
        //
        //
        const Val* data = 0;

        //
        //
        //
        isize items = 0;

        //
        //
        //
        Array() = default;

        //
        //
        //
        template <isize Len>
        constexpr Array(const Val (&seq)[Len]);

        //
        //
        //
        const Val&
        operator[](isize index) const;

        //
        //
        //
        Val&
        operator[](isize index);
    };

    //
    //
    // Implementation
    //
    //

    template <class Val>
    template <isize Len>
    constexpr Array<Val>::Array(const Val (&seq)[Len])
        : data {seq}
        , items {Len}
    {}

    template <class Val>
    const Val&
    Array<Val>::operator[](isize index) const
    {
        gr_exec_expect(0 < index && index <= items,
            "The index must be in range");

        return data[index - 1];
    }

    template <class Val>
    Val&
    Array<Val>::operator[](isize index)
    {
        gr_exec_expect(0 < index && index <= items,
            "The index must be in range");

        return data[index - 1];
    }
} // namespace gr

#endif // GR_CORE_ARRAY_HPP
