#ifndef SCENT_HANDLE_HPP
#define SCENT_HANDLE_HPP

#include <assert.h>

#include "types.hpp"

namespace scent
{
    template <class Val>
    struct Registry;

    template <class Val>
    struct Handle
    {
    private:
        /**
         *
         */
        Registry<Val>* _regty = 0;

        /**
         *
         */
        u32 _desc = 0;

        /**
         *
         */
        u32 _iter = 0;

    public:
        Handle();

        Handle(Registry<Val>& registry, u32 desc, u32 iter);

        void
        init(Registry<Val>& registry, u32 desc, u32 iter);

        void
        drop();

        bool
        is_valid() const;

        u32
        desc() const;

        u32
        iter() const;

        const Val&
        value() const;

        Val&
        value();
    };
} // scent

#include "handle.inl"

#endif // SCENT_HANDLE_HPP
