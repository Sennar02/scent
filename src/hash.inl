#include "hash.hpp"

namespace scent
{
    template <>
    u32
    Hash<u32>::get(const u32& key)
    {
        return key;
    }

    template <>
    bool
    Hash<u32>::eql(const u32& k1, const u32& k2)
    {
        return k1 == k2;
    }

    template <>
    u32
    Hash<u16>::get(const u16& key)
    {
        return key;
    }

    template <>
    bool
    Hash<u16>::eql(const u16& k1, const u16& k2)
    {
        return k1 == k2;
    }

    template <>
    u32
    Hash<u8>::get(const u8& key)
    {
        return key;
    }

    template <>
    bool
    Hash<u8>::eql(const u8& k1, const u8& k2)
    {
        return k1 == k2;
    }

    template <>
    u32
    Hash<i32>::get(const i32& key)
    {
        return key;
    }

    template <>
    bool
    Hash<i32>::eql(const i32& k1, const i32& k2)
    {
        return k1 == k2;
    }

    template <>
    u32
    Hash<i16>::get(const i16& key)
    {
        return key;
    }

    template <>
    bool
    Hash<i16>::eql(const i16& k1, const i16& k2)
    {
        return k1 == k2;
    }

    template <>
    u32
    Hash<i8>::get(const i8& key)
    {
        return key;
    }

    template <>
    bool
    Hash<i8>::eql(const i8& k1, const i8& k2)
    {
        return k1 == k2;
    }
} // scent
