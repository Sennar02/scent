// todo(trakot): work to remove.
#include <SDL3/SDL.h>

#include "window.hpp"
#include "keyboard.hpp"
#include "stage.hpp"
#include "application.hpp"

using namespace scent;

struct Test_Stage
    : public Stage
{
private:
    Window   window;
    Keyboard keyboard;

public:
    Test_Stage() {}

    bool
    init(Application& app)
    {
        window.init("Prova", {640u, 360u});
        keyboard.init();

        app.init_window(window);
        app.init_keyboard(keyboard);

        window.show();

        return true;
    }

    void
    drop()
    {
        window.drop();
        keyboard.drop();
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
        Vec4<f32> rect = {10.0f, 10.0f, 620.0f, 340.0f};

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
