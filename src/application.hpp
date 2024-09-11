#ifndef SCENT_APPLICATION_HPP
#define SCENT_APPLICATION_HPP

#include "clock.hpp"
#include "window.hpp"
#include "keyboard.hpp"
#include "stage.hpp"
#include "item_ref.hpp"

namespace scent
{
    struct Application
    {
    private:
        /**
         *
         */
        Clock _clck;

        /**
         *
         */
        Window* _wndw = 0;

        /**
         *
         */
        Keyboard* _kybd = 0;

        /**
         *
         */
        bool _actv = false;

    public:
        /**
         *
         */
        Application();

        /**
         *
         */
        void
        init();

        /**
         *
         */
        void
        drop();

        /**
         *
         */
        bool
        is_active() const;

        /**
         *
         */
        void
        stop();

        /**
         *
         */
        void
        init_window(Window& window);

        /**
         *
         */
        void
        init_keyboard(Keyboard& keyboard);

        /**
         *
         */
        bool
        update();

        /**
         *
         */
        bool
        signal();

        /**
         *
         */
        void
        loop(Stage& stage, f32 frames);
    };
} // scent

#endif // SCENT_APPLICATION_HPP
