#define SDL_MAIN_HANDLED
#include "..\\lib\\R1\\objects.hpp"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

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

    loadTextures();
    createObjects();

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


    for (auto obj : M_RenderableList) {
            delete obj;
        }
    M_RenderableList.clear();
    SDL_Log("[SDL_AppQuit]: Cleaned up M_RenderableList");

    for (auto& tex : M_TexturesList) {
        if (tex) {
            SDL_DestroyTexture(tex);
            tex = nullptr;
        }
    }
    M_TexturesList.clear();
    SDL_Log("[SDL_AppQuit]: Cleaned up M_TexturesList");
    
    
    SDL_Quit();
}