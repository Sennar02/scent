#ifndef SCENT_LOADER_HPP
#define SCENT_LOADER_HPP

#include "types.hpp"

namespace scent
{
    template <class Val>
    struct Loader
    {
    public:
        virtual Val
        load(const i8* name) = 0;

        virtual void
        unload(Val value) = 0;
    };
} // scent

#endif // SCENT_LOADER_HPP
