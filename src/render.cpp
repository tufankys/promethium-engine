#define SDL_MAIN_HANDLED
#include "..\\lib\\R1\\objects.hpp"

//M_TextureObject* player = nullptr;
//M_TextObject* testText = nullptr;

//run every frame
SDL_AppResult SDL_AppIterate(void *appstate) {
    M_SetDrawColor(renderer, 0, 0, 0);
    SDL_RenderClear(renderer);
    
    //M_SetDrawColor(renderer, 255, 255, 255);
    M_RenderDebugText(renderer, 0, 0, std::to_string(player->cordX).c_str());
    M_RenderDebugText(renderer, 25, 0, ",");
    M_RenderDebugText(renderer, 34, 0, std::to_string(player->cordY).c_str());

    for (M_Renderable* renderable : M_RenderableList) {
        if (renderable && renderable->willRender) {
            renderable->render(renderer);
        }
    }

    SDL_RenderPresent(renderer);
    return SDL_APP_CONTINUE;
}