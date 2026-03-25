#define SDL_MAIN_HANDLED
#include ".\\lib\\R1\\ring1.hpp"

//run once at the start
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {

    //SDL_SetAppMetadata("Promethium Engine", "1.0", "com.promethium-engine");

    if (!SDL_Init(SDL_INIT_VIDEO)) { 
        SDL_Log("[!SDL_AppInit]: SDL_Init error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!TTF_Init()) {
        SDL_Log("[!SDL_AppInit]: TTF_Init error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer(WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("[!SDL_AppInit]: Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    font = TTF_OpenFont("..\\assets\\fonts\\comic.ttf", 16);
    if (!font) {
        SDL_Log("[!SDL_AppInit]: Couldn't create font: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderLogicalPresentation(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    
    R1_AppInit();

    return SDL_APP_CONTINUE;
}




void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }

    R1_AppQuit();
    
    TTF_Quit();
    SDL_Quit();
}