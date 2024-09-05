#ifndef SCENT_WINDOW_HPP
#define SCENT_WINDOW_HPP

#include "types.hpp"
#include "vec2.hpp"
#include "vec4.hpp"
#include "colour.hpp"

struct SDL_Window;
struct SDL_Renderer;

namespace scent
{
    struct Window_Signal
    {
    public:
        enum class Type
            : u32
        {
            SHOW = 1,
            HIDE = 2,
            MOVE = 3,

            COUNT = MOVE,
        };

    public:
        Type type;

        union {
            // RESIZE, PIXEL_SIZE_CHANGE.
            Vec2<i32> size;

            // MOVE.
            Vec2<i32> coords;

            // SCREEN_CHANGE.
            i32 screen;
        };

    public:
        Window_Signal(Type type);
    };

    struct Window
    {
    private:
        SDL_Window*   _wndw = 0;
        SDL_Renderer* _rndr = 0;
        bool          _vsbl = false;

    public:
        Window();

        Window(const i8* title, Vec2<u32> size);

        void
        init(const i8* title, Vec2<u32> size);

        void
        drop();

        u32
        code() const;

        bool
        is_visible() const;

        bool
        isnt_visible() const;

        void
        show();

        void
        hide();

        void
        fill_rect(Vec4<f32> rect, Colour colour);

        void
        draw_rect(Vec4<f32> rect, Colour colour);

        void
        render();

        void
        render(Colour colour);

        bool
        update(Window_Signal signal);
    };
} // scent

#endif // SCENT_WINDOW_HPP
