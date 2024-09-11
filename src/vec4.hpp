#ifndef SCENT_VEC4_HPP
#define SCENT_VEC4_HPP

#include "slice.hpp"

namespace scent
{
    template <class Val>
    struct Vec4
    {
    public:
        /**
         *
         */
        Val a = {};

        /**
         *
         */
        Val b = {};

        /**
         *
         */
        Val c = {};

        /**
         *
         */
        Val d = {};

    public:
        /**
         *
         */
        Vec4();

        /**
         *
         */
        Vec4(Val val);

        /**
         *
         */
        Vec4(Val a, Val b, Val c, Val d);

        /**
         *
         */
        Slice<const Val>
        values() const;

        /**
         *
         */
        Slice<Val>
        values();

        /**
         *
         */
        Vec4
        operator+(const Vec4<Val>& vec) const;

        /**
         *
         */
        Vec4
        operator+(Val val) const;

        /**
         *
         */
        Vec4
        operator-(const Vec4<Val>& vec) const;

        /**
         *
         */
        Vec4
        operator-(Val val) const;

        /**
         *
         */
        Vec4
        operator*(const Vec4<Val>& vec) const;

        /**
         *
         */
        Vec4
        operator*(Val val) const;

        /**
         *
         */
        Vec4
        operator/(const Vec4<Val>& vec) const;

        /**
         *
         */
        Vec4
        operator/(Val val) const;
    };
} // scent

#include "vec4.inl"

#endif // SCENT_VEC4_HPP
