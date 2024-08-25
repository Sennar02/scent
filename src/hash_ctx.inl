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
} // scent
