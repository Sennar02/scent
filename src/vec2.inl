#include "vec2.hpp"

namespace scent
{
    template <class Val>
    Vec2<Val>::Vec2() {}

    template <class Val>
    Vec2<Val>::Vec2(Val val)
        : a {val}
        , b {val}
    {}

    template <class Val>
    Vec2<Val>::Vec2(Val a, Val b)
        : a {a}
        , b {b}
    {}

    template <class Val>
    Slice<const Val>
    Vec2<Val>::values() const
    {
        return {&a, 2u};
    }

    template <class Val>
    Slice<Val>
    Vec2<Val>::values()
    {
        return {&a, 2u};
    }

    template <class Val>
    Vec2<Val>
    Vec2<Val>::operator+(const Vec2<Val>& vec) const
    {
        return {a + vec.a, b + vec.b};
    }

    template <class Val>
    Vec2<Val>
    Vec2<Val>::operator+(Val val) const
    {
        return {a + val, b + val};
    }

    template <class Val>
    Vec2<Val>
    Vec2<Val>::operator-(const Vec2<Val>& vec) const
    {
        return {a - vec.a, b - vec.b};
    }

    template <class Val>
    Vec2<Val>
    Vec2<Val>::operator-(Val val) const
    {
        return {a - val, b - val};
    }

    template <class Val>
    Vec2<Val>
    Vec2<Val>::operator*(const Vec2<Val>& vec) const
    {
        return {a * vec.a, b * vec.b};
    }

    template <class Val>
    Vec2<Val>
    Vec2<Val>::operator*(Val val) const
    {
        return {a * val, b * val};
    }

    template <class Val>
    Vec2<Val>
    Vec2<Val>::operator/(const Vec2<Val>& vec) const
    {
        return {a / vec.a, b / vec.b};
    }

    template <class Val>
    Vec2<Val>
    Vec2<Val>::operator/(Val val) const
    {
        return {a / val, b / val};
    }
} // scent
