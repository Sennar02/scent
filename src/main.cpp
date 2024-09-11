// todo(trakot): work to remove.
#include <SDL3/SDL.h>
#include <stdio.h>
#include <malloc.h>

#include "arena_alloc.hpp"
#include "window.hpp"
#include "keyboard.hpp"
#include "stage.hpp"
#include "application.hpp"
#include "emitter.hpp"

using namespace scent;

void
keyboard_handler(Keyboard_Signal signal)
{
    const i8* names[] = {
        "down", "up",
    };

    printf("[%s]\n", names[signal.type - 1u]);
}

struct Test_Stage
    : public Stage
{
private:
    Arena_Alloc arena;

    Window   window;
    Keyboard keyboard;

public:
    Test_Stage() {}

    bool
    init(Application& app)
    {
        arena.init(malloc(8192u), 8192u);

        window.init("Prova", {640u, 360u});
        window.init_emitter(arena, 32u);
        keyboard.init();
        keyboard.init_emitter(arena, 32u);

        app.init_window(window);
        app.init_keyboard(keyboard);

        keyboard.attach(&keyboard_handler);

        window.show();

        return true;
    }

    void
    drop()
    {
        keyboard.drop();
        window.drop();

        arena.drop();
    }

    bool
    input()
    {
        if ( keyboard.is_now_up(SDL_SCANCODE_ESCAPE) )
            return false;

        return true;
    }

    void
    frame()
    {}

    void
    tick(f32)
    {}

    void
    draw()
    {
        Vec4<f32> rect = {
            10.0f, 10.0f, 620.0f, 340.0f,
        };

        window.fill_rect(rect, COLOUR_BLACK);
        window.render(COLOUR_WHITE);
    }
};

static Test_Stage  stage;
static Application app;

int
main()
{
    app.init();
    app.loop(stage, 60.0f);
    app.drop();
}
