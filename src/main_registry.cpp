#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <malloc.h>

#include "application.hpp"
#include "stage.hpp"
#include "window.hpp"
#include "keyboard.hpp"
#include "arena_alloc.hpp"
#include "loader.hpp"
#include "handle.hpp"
#include "registry.hpp"

using namespace scent;

struct Surface_Loader
    : public Loader<SDL_Surface*>
{
public:
    SDL_Surface*
    load(const i8* name)
    {
        auto pntr = IMG_Load(name);

        assert(pntr != 0);

        return pntr;
    }

    void
    unload(SDL_Surface* value)
    {
        SDL_DestroySurface(value);
    }
};

struct Testing
    : public Stage
{
private:
    Arena_Alloc arena;

    Window   window;
    Keyboard keyboard;

    Registry<SDL_Surface*> surfaces;

    Handle<SDL_Surface*> _bg;

public:
    Testing() {}

    bool
    init(Application& app)
    {
        arena.init(malloc(8192u), 8192u);

        window.init("Prova", {640u, 360u});
        keyboard.init();

        app.init_window(window);
        app.init_keyboard(keyboard);

        Surface_Loader loader;

        surfaces.init(arena, 5u);
        surfaces.init_loader(loader);

        _bg = surfaces.acquire("./res/bg.png");

        printf("backg = %u v%u\n", _bg.desc(), _bg.iter());

        surfaces.release(_bg);

        _bg = surfaces.acquire("./res/bg.png");

        printf("backg = %u v%u\n", _bg.desc(), _bg.iter());

        auto trash = surfaces.acquire("./res/bg.png");

        printf("trash = %u v%u\n", trash.desc(), trash.iter());

        surfaces.release(trash);
        surfaces.release(_bg);

        _bg = surfaces.acquire("./res/bg.png");

        printf("backg = %u v%u\n", _bg.desc(), _bg.iter());

        window.show();

        return true;
    }

    void
    drop()
    {
        surfaces.release(_bg);
        surfaces.drop();

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
        window.draw(*_bg.value());
        window.render(COLOUR_WHITE);
    }
};

int
main()
{
    Application app;
    Testing     stage;

    app.init();
    app.loop(stage, 60.0f);
    app.drop();
}
