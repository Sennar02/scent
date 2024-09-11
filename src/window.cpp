#include <SDL3/SDL.h>

#include "window.hpp"

namespace scent
{
    Window_Signal::Window_Signal()
        : type {UNDEF}
        , size {}
    {}

    Window::Window() {}

    Window::Window(const i8* title, Vec2<u32> size)
    {
        init(title, size);
    }

    void
    Window::init(const i8* title, Vec2<u32> size)
    {
        u32 flags = SDL_WINDOW_HIDDEN;

        assert(size.a != 0 && "Window width is zero.");
        assert(size.b != 0 && "Window height is zero.");

        if ( _wndw != 0 ) drop();

        _wndw = SDL_CreateWindow(title, size.a, size.b, flags);

        if ( _wndw != 0 ) {
            _rndr = SDL_CreateRenderer(_wndw, 0);

            if ( _rndr != 0 ) {
                SDL_SetRenderDrawBlendMode(_rndr, SDL_BLENDMODE_BLEND);
                SDL_RenderClear(_rndr);
            }
        }
    }

    void
    Window::init_emitter(Alloc& alloc, u32 size)
    {
        _emtr.init(alloc, size);
    }

    void
    Window::drop()
    {
        if ( _wndw == 0 || _rndr == 0 )
            return;

        SDL_DestroyRenderer(_rndr);
        SDL_DestroyWindow(_wndw);

        _wndw = 0;
        _rndr = 0;

        _emtr.drop();
    }

    u32
    Window::code() const
    {
        if ( _wndw != 0 )
            return SDL_GetWindowID(_wndw);

        return 0;
    }

    bool
    Window::is_visible() const
    {
        return _vsbl;
    }

    bool
    Window::isnt_visible() const
    {
        return _vsbl == false;
    }

    Vec2<i32>
    Window::coords() const
    {
        Vec2<i32> coords;

        if ( _wndw != 0 )
            SDL_GetWindowPosition(_wndw, &coords.a, &coords.b);

        return coords;
    }

    void
    Window::show()
    {
        if ( _wndw != 0 ) SDL_ShowWindow(_wndw);
    }

    void
    Window::hide()
    {
        if ( _wndw != 0 ) SDL_HideWindow(_wndw);
    }

    void
    Window::move(Vec2<i32> coords)
    {
        if ( _wndw != 0 ) SDL_SetWindowPosition(_wndw, coords.a, coords.b);
    }

    void
    Window::fill_rect(Vec4<f32> rect, Colour colour)
    {
        if ( _rndr == 0 ) return;

        SDL_FRect fill = {rect.a, rect.b, rect.c, rect.d};

        SDL_SetRenderDrawColor(_rndr,
            colour.a, colour.b, colour.c, colour.d
        );

        SDL_RenderFillRect(_rndr, &fill);
        SDL_SetRenderDrawColor(_rndr, 0, 0, 0, 0);
    }

    void
    Window::draw_rect(Vec4<f32> rect, Colour colour)
    {
        if ( _rndr == 0 ) return;

        SDL_FRect fill = {rect.a, rect.b, rect.c, rect.d};

        SDL_SetRenderDrawColor(_rndr,
            colour.a, colour.b, colour.c, colour.d
        );

        SDL_RenderRect(_rndr, &fill);
        SDL_SetRenderDrawColor(_rndr, 0, 0, 0, 0);
    }

    void
    Window::render()
    {
        if ( _rndr == 0 ) return;

        SDL_RenderPresent(_rndr);
        SDL_RenderClear(_rndr);
    }

    void
    Window::render(Colour colour)
    {
        if ( _rndr == 0 ) return;

        SDL_SetRenderDrawColor(_rndr,
            colour.a, colour.b, colour.c, colour.d
        );

        SDL_RenderPresent(_rndr);
        SDL_RenderClear(_rndr);
        SDL_SetRenderDrawColor(_rndr, 0, 0, 0, 0);
    }

    bool
    Window::attach(void (*fptr) (Window_Signal))
    {
        return _emtr.attach(fptr);
    }

    template <class Ctx>
    bool
    Window::attach(void (*fptr) (Ctx&, Window_Signal), Ctx& self)
    {
        return _emtr.attach(fptr, self);
    }

    template <class Ctx>
    bool
    Window::attach(void (*fptr) (const Ctx&, Window_Signal), Ctx& self)
    {
        return _emtr.attach(fptr, self);
    }

    void
    Window::update()
    {}

    void
    Window::signal(const Window_Signal& signal)
    {
        switch ( signal.type ) {
            case Window_Signal::SHOW: {
                _vsbl = true;
            } break;

            case Window_Signal::HIDE: {
                _vsbl = false;
            } break;

            case Window_Signal::MOVE:
            case Window_Signal::UNDEF:
                break;
        }

        _emtr.emit(signal);
    }
} // scent
