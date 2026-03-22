#include "..\\lib\\app.hpp"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;

//run once at the start
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {

    SDL_SetAppMetadata("Promethium Engine", "1.0", "com.promethium-engine");

    if (!SDL_Init(SDL_INIT_VIDEO)) { 
        SDL_Log("SDL_Init error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Promethium Engine", 640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderLogicalPresentation(renderer, 640, 480, SDL_LOGICAL_PRESENTATION_LETTERBOX);


    SDL_Surface* surface = NULL;
    char* png_path = NULL;

    SDL_asprintf(&png_path, "%s..\\lib\\sample.png", SDL_GetBasePath());
    surface = SDL_LoadPNG(png_path);
    if (!surface) {
        SDL_Log("Couldn't load png: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_free(png_path);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_Log("Couldn't create static texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_DestroySurface(surface);
    return SDL_APP_CONTINUE;
}




void SDL_AppQuit(void *appstate, SDL_AppResult result) {

}