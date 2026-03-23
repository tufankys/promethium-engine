#define SDL_MAIN_HANDLED
#include "..\\lib\\R1\\objects.hpp"

//extern M_TextureObject* player;

//event
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) return SDL_APP_SUCCESS;
    
    if (event->type == SDL_EVENT_KEY_DOWN) {
        switch (event->key.key) {
            case SDLK_W: player->cordY--; break;
            case SDLK_A: player->cordX--; break;
            case SDLK_S: player->cordY++; break;
            case SDLK_D: player->cordX++; break;
        }
    }
    
    return SDL_APP_CONTINUE;
}