#ifndef SCENT_HASH_CTX_HPP
#define SCENT_HASH_CTX_HPP

#include "types.hpp"

namespace scent
{
    template <class Key>
    struct Hash_Ctx final
    {
        /**
         *
         */
        static u32
        hash(const Key& key);

        /**
         *
         */
        static bool
        equals(const Key& k1, const Key& k2);
    };
} // namespace scent

#include "hash_ctx.inl"

#endif // SCENT_HASH_CTX_HPP
