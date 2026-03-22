#include "..\\lib\\app.hpp"

M_TextureObject player(320, 240, 90, 90);
std::vector<SDL_Texture*> textures = {};

//run every frame
SDL_AppResult SDL_AppIterate(void *appstate) {
    M_SetDrawColor(renderer, 0, 0, 0);
    SDL_RenderClear(renderer);

    M_SetDrawColor(renderer, 255, 255, 255);
    M_RenderDebugText(renderer, 0, 0, std::to_string(player.x).c_str());
    M_RenderDebugText(renderer, 25, 0, ",");
    M_RenderDebugText(renderer, 34, 0, std::to_string(player.y).c_str());

    player.render(renderer, M_FindTexture("sample.png") );

    SDL_RenderPresent(renderer);
    return SDL_APP_CONTINUE;
}