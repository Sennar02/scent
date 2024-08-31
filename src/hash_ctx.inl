#include "hash_ctx.hpp"

namespace scent
{
    template <>
    u32
    Hash_Ctx<u32>::hash(const u32& key)
    {
        return key;
    }

    template <>
    bool
    Hash_Ctx<u32>::equals(const u32& k1, const u32& k2)
    {
        return k1 == k2;
    }

    template <>
    u32
    Hash_Ctx<u16>::hash(const u16& key)
    {
        return key;
    }

    template <>
    bool
    Hash_Ctx<u16>::equals(const u16& k1, const u16& k2)
    {
        return k1 == k2;
    }

    template <>
    u32
    Hash_Ctx<u8>::hash(const u8& key)
    {
        return key;
    }

    template <>
    bool
    Hash_Ctx<u8>::equals(const u8& k1, const u8& k2)
    {
        return k1 == k2;
    }

    template <>
    u32
    Hash_Ctx<i32>::hash(const i32& key)
    {
        return key;
    }

    template <>
    bool
    Hash_Ctx<i32>::equals(const i32& k1, const i32& k2)
    {
        return k1 == k2;
    }

    template <>
    u32
    Hash_Ctx<i16>::hash(const i16& key)
    {
        return key;
    }

    template <>
    bool
    Hash_Ctx<i16>::equals(const i16& k1, const i16& k2)
    {
        return k1 == k2;
    }

    template <>
    u32
    Hash_Ctx<i8>::hash(const i8& key)
    {
        return key;
    }

    template <>
    bool
    Hash_Ctx<i8>::equals(const i8& k1, const i8& k2)
    {
        return k1 == k2;
    }

    template <>
    u32
    Hash_Ctx<const i8*>::hash(const i8* const& key)
    {
        u32       hash = 5381u;
        const i8* pntr = key;

        if ( pntr == 0 ) return hash;

        while ( *pntr != 0 ) {
            hash =  ((hash << 5u) + hash) + *pntr;
            pntr += 1u;
        }

        return hash;
    }

    template <>
    bool
    Hash_Ctx<const i8*>::equals(const i8* const& k1, const i8* const& k2)
    {
        const i8* ptr1 = k1;
        const i8* ptr2 = k2;

        if ( ptr1 == 0 || ptr2 == 0 )
            return false;

        while ( *ptr1 != 0 ) {
            if ( *ptr1 != *ptr2 ) return false;

            ptr1 += 1u;
            ptr2 += 1u;
        }

        return true;
    }
} // scent
