#ifndef GR_CORE_ARRAY_HPP
#define GR_CORE_ARRAY_HPP

#include "types.hpp"

namespace gr
{
    template <class Val, isize Len>
    struct Array {
        //
        //
        //
        static const isize items = Len;

        //
        //
        //
        Val data[Len];

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
    // Implementation.
    //
    //

    template <class Val, isize Len>
    const Val&
    Array<Val, Len>::operator[](isize index) const
    {
        gr_exec_expect(0 < index && index <= items,
            "The index must be in range");

        return data[index - 1];
    }

    template <class Val, isize Len>
    Val&
    Array<Val, Len>::operator[](isize index)
    {
        gr_exec_expect(0 < index && index <= items,
            "The index must be in range");

        return data[index - 1];
    }
} // namespace gr

#endif // GR_CORE_ARRAY_HPP
