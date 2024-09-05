#ifndef SCENT_VEC2_HPP
#define SCENT_VEC2_HPP

#include "slice.hpp"

namespace scent
{
    template <class Val>
    struct Vec2
    {
    public:
        Val a = {};
        Val b = {};

    public:
        Vec2();

        Vec2(Val val);

        Vec2(Val a, Val b);

        Slice<const Val>
        values() const;

        Slice<Val>
        values();

        Vec2
        operator+(const Vec2<Val>& vec) const;

        Vec2
        operator+(Val val) const;

        Vec2
        operator-(const Vec2<Val>& vec) const;

        Vec2
        operator-(Val val) const;

        Vec2
        operator*(const Vec2<Val>& vec) const;

        Vec2
        operator*(Val val) const;

        Vec2
        operator/(const Vec2<Val>& vec) const;

        Vec2
        operator/(Val val) const;
    };
} // scent

#include "vec2.inl"

#endif // SCENT_VEC2_HPP
