#include "..\\lib\\app.hpp"

//event
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) return SDL_APP_SUCCESS;

    if (event->type == SDL_EVENT_KEY_DOWN) {
        switch (event->key.key) {
            case SDLK_W: player.y--; break;
            case SDLK_A: player.x--; break;
            case SDLK_S: player.y++; break;
            case SDLK_D: player.x++; break;
        }
    }
    return SDL_APP_CONTINUE;
}