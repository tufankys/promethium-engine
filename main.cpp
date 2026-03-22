#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */

#include "lib\player.hpp"
using namespace std;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;

M_TextureObject player(320,240,90,90);


//run once at startup
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    SDL_Surface *surface = NULL;
    char *png_path = NULL;

    SDL_SetAppMetadata("Promethium Engine", "1.0", "com.promethium-engine");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Promethium Engine", 640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderLogicalPresentation(renderer, 640, 480, SDL_LOGICAL_PRESENTATION_LETTERBOX);


    //Load Texture
    SDL_asprintf( &png_path, "%ssample.png", SDL_GetBasePath() );
    surface = SDL_LoadPNG(png_path);
    if (!surface) {
        SDL_Log("Couldn't load png: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_free(png_path);  /* done with this, the file is loaded. */

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_Log("Couldn't create static texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_DestroySurface(surface);  /* done with this, the texture has a copy of the pixels now. */
    //

    return SDL_APP_CONTINUE;
}



//event
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    if (event->type == SDL_EVENT_KEY_DOWN) {

        switch (event->key.key) {
        case SDLK_W:
            player.y--;
            break;

        case SDLK_A:
            player.x--;
            break;

        case SDLK_S:
            player.y++;
            break;

        case SDLK_D:
            player.x++;
            break;
        
        default:
            break;
        }

    }
    return SDL_APP_CONTINUE;
}



//heartbeat
SDL_AppResult SDL_AppIterate(void *appstate) {
    //SDL_FRect dst_rect;
    //const int charsize = SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;

    M_SetDrawColor(renderer, 0,0,0);
    SDL_RenderClear(renderer);

    M_SetDrawColor(renderer, 255,255,255);
    M_RenderDebugText(renderer, 0, 0, to_string(player.x).c_str() );
    M_RenderDebugText(renderer, 25, 0, "," );
    M_RenderDebugText(renderer, 34, 0, to_string(player.y).c_str() );

    player.render(renderer, texture);
    
    SDL_RenderPresent(renderer);
    return SDL_APP_CONTINUE;
}



//quit
void SDL_AppQuit(void *appstate, SDL_AppResult result) {

}
