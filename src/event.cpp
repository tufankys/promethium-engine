#define SDL_MAIN_HANDLED
#include ".\\lib\\R1\\ring1.hpp"

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {    
    if (event->type == SDL_EVENT_QUIT) return SDL_APP_SUCCESS;
    R1_SdlEvent(appstate, event);
    return SDL_APP_CONTINUE;
}