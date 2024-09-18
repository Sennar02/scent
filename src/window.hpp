#ifndef SCENT_WINDOW_HPP
#define SCENT_WINDOW_HPP

#include "types.hpp"
#include "vec2.hpp"
#include "vec4.hpp"
#include "colour.hpp"
#include "channel.hpp"

struct SDL_Window;
struct SDL_Renderer;

namespace scent
{
    struct Window_Msg
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
        Window_Msg();
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
        Channel<Window_Msg> _chnl;

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
        init_channel(Alloc& alloc, u32 size);

        /**
         *
         */
        void
        drop();

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
        u32
        desc() const;

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
        draw(Vec4<f32> rect, SDL_Surface& surface);

        /**
         *
         */
        void
        draw(SDL_Surface& surface);

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
        attach(void (*fptr) (Window_Msg));

        /**
         *
         */
        template <class Ctx>
        bool
        attach(Ctx& self, void (*fptr) (Ctx&, Window_Msg));

        /**
         *
         */
        template <class Ctx>
        bool
        attach(Ctx& self, void (*fptr) (const Ctx&, Window_Msg));

        /**
         *
         */
        void
        update();

        /**
         *
         */
        void
        send(const Window_Msg& message);
    };
} // scent

#endif // SCENT_WINDOW_HPP
