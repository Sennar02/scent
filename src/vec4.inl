#include "vec4.hpp"

namespace scent
{
    template <class Val>
    Vec4<Val>::Vec4() {}

    template <class Val>
    Vec4<Val>::Vec4(Val val)
        : a {val}
        , b {val}
        , c {val}
        , d {val}
    {}

    template <class Val>
    Vec4<Val>::Vec4(Val a, Val b, Val c, Val d)
        : a {a}
        , b {b}
        , c {c}
        , d {d}
    {}

    template <class Val>
    Slice<const Val>
    Vec4<Val>::values() const
    {
        return {&a, 4u};
    }

    template <class Val>
    Slice<Val>
    Vec4<Val>::values()
    {
        return {&a, 4u};
    }

    template <class Val>
    Vec4<Val>
    Vec4<Val>::operator+(const Vec4<Val>& vec) const
    {
        return {a + vec.a, b + vec.b, c + vec.c, d + vec.d};
    }

    template <class Val>
    Vec4<Val>
    Vec4<Val>::operator+(Val val) const
    {
        return {a + val, b + val, c + val, d + val};
    }

    template <class Val>
    Vec4<Val>
    Vec4<Val>::operator-(const Vec4<Val>& vec) const
    {
        return {a - vec.a, b - vec.b, c - vec.c, d - vec.d};
    }

    template <class Val>
    Vec4<Val>
    Vec4<Val>::operator-(Val val) const
    {
        return {a - val, b - val, c - val, d - val};
    }

    template <class Val>
    Vec4<Val>
    Vec4<Val>::operator*(const Vec4<Val>& vec) const
    {
        return {a * vec.a, b * vec.b, c * vec.c, d * vec.d};
    }

    template <class Val>
    Vec4<Val>
    Vec4<Val>::operator*(Val val) const
    {
        return {a * val, b * val, c * val, d * val};
    }

    template <class Val>
    Vec4<Val>
    Vec4<Val>::operator/(const Vec4<Val>& vec) const
    {
        return {a / vec.a, b / vec.b, c / vec.c, d / vec.d};
    }

    template <class Val>
    Vec4<Val>
    Vec4<Val>::operator/(Val val) const
    {
        return {a / val, b / val, c / val, d / val};
    }
} // scent
