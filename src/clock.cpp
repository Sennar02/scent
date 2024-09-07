#include <SDL3/SDL.h>

#include "clock.hpp"

namespace scent
{
    Clock::Clock() {}

    void
    Clock::init()
    {}

    void
    Clock::drop()
    {
        _time = 0;
        _next = 0;
    }

    f32
    Clock::time() const
    {
        return _next / 1000.0f;
    }

    f32
    Clock::update()
    {
        _time = _next;
        _next = SDL_GetTicks();

        return (_next - _time) / 1000.0f;
    }
} // scent

