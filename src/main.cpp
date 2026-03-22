//#define SDL_MAIN_USE_CALLBACKS 1
//#define SDL_MAIN_HANDLED
#include "..\\lib\\app.hpp"

int main(int argc, char* argv[]) {
    //SDL_SetMainReady();

    void* appstate = nullptr;
    if (SDL_AppInit(&appstate, argc, argv) != SDL_APP_CONTINUE) {
        return -1;
    }

    SDL_Event event;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (SDL_AppEvent(appstate, &event) == SDL_APP_SUCCESS) {
                running = false;
            }
        }

        if (SDL_AppIterate(appstate) != SDL_APP_CONTINUE) {
            running = false;
        }
    }

    SDL_AppQuit(appstate, SDL_APP_SUCCESS);
    return 0;
}