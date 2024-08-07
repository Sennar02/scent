#ifndef SCENT_HASH_HPP
#define SCENT_HASH_HPP

#include "types.hpp"

namespace scent
{
    template <class Key>
    struct Hash final
    {
        /**
         *
         */
        static u32
        get(const Key& key);

        /**
         *
         */
        static bool
        eql(const Key& k1, const Key& k2);
    };
} // namespace scent

#include "hash.inl"

#endif // SCENT_HASH_HPP
