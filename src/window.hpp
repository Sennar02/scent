#ifndef SCENT_WINDOW_HPP
#define SCENT_WINDOW_HPP

#include "types.hpp"
#include "vec2.hpp"
#include "vec4.hpp"
#include "colour.hpp"
#include "emitter.hpp"

struct SDL_Window;
struct SDL_Renderer;

namespace scent
{
    struct Window_Signal
    {
    public:
        enum Type
            : u32
        {
            UNDEF = 0,
            SHOW  = 1u,
            HIDE  = 2u,
            MOVE  = 3u,

            COUNT = MOVE,
        };

    public:
        /**
         *
         */
        Type type;

        union {
            /**
             * RESIZE, PIXEL_SIZE_CHANGE.
             */
            Vec2<i32> size;

            /**
             * MOVE.
             */
            Vec2<i32> coords;

            /**
             * SCREEN_CHANGE.
             */
            i32 screen;
        };

    public:
        /**
         *
         */
        Window_Signal();
    };

    struct Window
    {
    private:
        /**
         *
         */
        SDL_Window* _wndw = 0;

        /**
         *
         */
        SDL_Renderer* _rndr = 0;

        /**
         *
         */
        Emitter<Window_Signal> _emtr;

        /**
         *
         */
        bool _vsbl = false;

    public:
        /**
         *
         */
        Window();

        /**
         *
         */
        Window(const i8* title, Vec2<u32> size);

        /**
         *
         */
        void
        init(const i8* title, Vec2<u32> size);

        /**
         *
         */
        void
        init_emitter(Alloc& alloc, u32 size);

        /**
         *
         */
        void
        drop();

        /**
         *
         */
        u32
        code() const;

        /**
         *
         */
        bool
        is_visible() const;

        /**
         *
         */
        bool
        isnt_visible() const;

        /**
         *
         */
        Vec2<i32>
        coords() const;

        /**
         *
         */
        void
        show();

        /**
         *
         */
        void
        hide();

        /**
         *
         */
        void
        move(Vec2<i32> coords);

        /**
         *
         */
        void
        fill_rect(Vec4<f32> rect, Colour colour);

        /**
         *
         */
        void
        draw_rect(Vec4<f32> rect, Colour colour);

        /**
         *
         */
        void
        render();

        /**
         *
         */
        void
        render(Colour colour);

        /**
         *
         */
        bool
        attach(void (*fptr) (Window_Signal));

        /**
         *
         */
        template <class Ctx>
        bool
        attach(void (*fptr) (Ctx&, Window_Signal), Ctx& self);

        /**
         *
         */
        template <class Ctx>
        bool
        attach(void (*fptr) (const Ctx&, Window_Signal), Ctx& self);

        /**
         *
         */
        void
        update();

        /**
         *
         */
        void
        signal(const Window_Signal& signal);
    };
} // scent

#endif // SCENT_WINDOW_HPP
