#define SDL_MAIN_HANDLED
#include ".\\lib\\R1\\ring1.hpp"

int main(int argc, char* argv[]) {

    void* appstate = nullptr;
    if (SDL_AppInit(&appstate, argc, argv) != SDL_APP_CONTINUE) {
        return -1;
    }
    

    SDL_Event event;
    running = true;
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