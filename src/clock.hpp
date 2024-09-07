#ifndef SCENT_CLOCK_HPP
#define SCENT_CLOCK_HPP

#include "types.hpp"

namespace scent
{
    struct Clock
    {
    private:
        u64 _time = 0;
        u64 _next = 0;

    public:
        Clock();

        void
        init();

        void
        drop();

        f32
        time() const;

        f32
        update();
    };
} // scent

#endif // SCENT_CLOCK_HPP

