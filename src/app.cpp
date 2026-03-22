#include "..\\lib\\app.hpp"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

//run once at the start
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {

    SDL_SetAppMetadata("Promethium Engine", "1.0", "com.promethium-engine");

    if (!SDL_Init(SDL_INIT_VIDEO)) { 
        SDL_Log("[!SDL_AppInit]: SDL_Init error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Promethium Engine", 640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("[!SDL_AppInit]: Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderLogicalPresentation(renderer, 640, 480, SDL_LOGICAL_PRESENTATION_LETTERBOX);


    SDL_Texture* texture = M_LoadTexture(renderer, "sample.png");

    return SDL_APP_CONTINUE;
}




void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    for (auto& tex : textures) {
        if (tex) {
            SDL_DestroyTexture(tex);
            tex = NULL;
        }
    }
    textures.clear();
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = NULL;
    }
    SDL_Quit();
}