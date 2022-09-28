#include "../libs/raylib/src/raylib.h"
#include "helper.hpp"
#include "Game.hpp"

Game *game;

void _loop() {
#if defined(PLATFORM_WEB)
    static int old_w=0,old_h=0;

    int w = getWindowWidth();
    int h = getWindowHeight();
    if(w!=old_w || h!=old_h){ SetWindowSize(w,h); }
#endif
    game->loop();
}

int main(void) {
    // Setup window
#if defined(PLATFORM_WEB)
    InitWindow(getBrowserWindowWidth(), getBrowserWindowHeight(), PROJECT_NAME);
#else
    InitWindow(800, 500, PROJECT_NAME);
#endif
    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED);

    game = new Game();

    // Setup assets
    #if defined(PLATFORM_WEB)
    emscripten_set_main_loop(_loop, 0, 1);
#else
    while (!WindowShouldClose()) {
        _loop();
    }
#endif

    delete game;
    // Cleanup
    CloseWindow();
    return 0;
}
