#define SDL_MAIN_HANDLED
#include ".\\lib\\R1\\ring1.hpp"

//run every frame
SDL_AppResult SDL_AppIterate(void *appstate) {
    M_SetDrawColor(renderer, 0, 0, 0);
    SDL_RenderClear(renderer);

    R1_Render();

    SDL_RenderPresent(renderer);
    return SDL_APP_CONTINUE;
}