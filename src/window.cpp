// todo(gio): rendi privato.
#include <stdio.h>

#include <assert.h>
#include <SDL3/SDL.h>

#include "window.hpp"

namespace scent
{
    Window_Signal::Window_Signal(Type type)
        : type {type}
        , size {0, 0}
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
    Window::drop()
    {
        assert(_rndr != 0 && "The window does not exist.");

        SDL_DestroyRenderer(_rndr);
        SDL_DestroyWindow(_wndw);

        _wndw = 0;
        _rndr = 0;
    }

    u32
    Window::code() const
    {
        assert(_rndr != 0 && "The window does not exist.");

        return SDL_GetWindowID(_wndw);
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

    void
    Window::show()
    {
        assert(_rndr != 0 && "The window does not exist.");

        _vsbl = true;

        SDL_ShowWindow(_wndw);
    }

    void
    Window::hide()
    {
        assert(_rndr != 0 && "The window does not exist.");

        _vsbl = false;

        SDL_HideWindow(_wndw);
    }

    void
    Window::fill_rect(Vec4<f32> rect, Colour colour)
    {
        assert(_rndr != 0 && "The window does not exist.");

        SDL_FRect fill = {
            rect.a, rect.b, rect.c, rect.d,
        };

        SDL_SetRenderDrawColor(_rndr,
            colour.a, colour.b, colour.c, colour.d
        );

        SDL_RenderFillRect(_rndr, &fill);
        SDL_SetRenderDrawColor(_rndr, 0, 0, 0, 0);
    }

    void
    Window::draw_rect(Vec4<f32> rect, Colour colour)
    {
        assert(_rndr != 0 && "The window does not exist.");

        SDL_FRect fill = {
            rect.a, rect.b, rect.c, rect.d,
        };

        SDL_SetRenderDrawColor(_rndr,
            colour.a, colour.b, colour.c, colour.d
        );

        SDL_RenderRect(_rndr, &fill);
        SDL_SetRenderDrawColor(_rndr, 0, 0, 0, 0);
    }

    void
    Window::render()
    {
        assert(_rndr != 0 && "The window does not exist.");

        SDL_RenderPresent(_rndr);
        SDL_RenderClear(_rndr);
    }

    void
    Window::render(Colour colour)
    {
        assert(_rndr != 0 && "The window does not exist.");

        SDL_SetRenderDrawColor(_rndr,
            colour.a, colour.b, colour.c, colour.d
        );

        SDL_RenderPresent(_rndr);
        SDL_RenderClear(_rndr);
        SDL_SetRenderDrawColor(_rndr, 0, 0, 0, 0);
    }

    bool
    Window::update(Window_Signal event)
    {
        if ( event.type == Window_Signal::Type::MOVE )
            printf("Window update [coords = (%u, %u)]\n",
                event.coords.a, event.coords.b
            );
        else
            printf("Window update\n");

        return true;
    }
} // scent
