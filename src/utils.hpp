#ifndef SCENT_UTILS_HPP
#define SCENT_UTILS_HPP

namespace scent
{
    /**
     *
     */
    template <class Val>
    Val
    extr(Val& v1, const Val& v2);

    /**
     *
     */
    template <class Val>
    void
    swap(Val& v1, Val& v2);
} // scent

#include "utils.inl"

#endif
