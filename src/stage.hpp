#ifndef SCENT_STAGE_HPP
#define SCENT_STAGE_HPP

#include "types.hpp"

namespace scent
{
    struct Application;

    struct Stage
    {
    public:
        virtual bool
        init(Application& app) = 0;

        virtual void
        drop() = 0;

        virtual bool
        input() = 0;

        virtual void
        frame() = 0;

        virtual void
        tick(f32 time) = 0;

        virtual void
        draw() = 0;
    };
} // scent

#endif // SCENT_STAGE_HPP

