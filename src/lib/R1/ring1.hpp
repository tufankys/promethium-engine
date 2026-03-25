#ifndef RING1_HPP
#define RING1_HPP

#include ".\\objects.hpp"

inline void R1_AppInit() {
    R1_loadTextures();
    R1_createObjects();
}

inline void R1_Render() {
    for (M_Renderable* renderable : M_RenderableList) {
        if (renderable && renderable->willRender) {
            renderable->render(renderer);
        }
    }

    testText->render(renderer);
}

inline void R1_SdlEvent(void *appstate, SDL_Event *event) {

    if (event->type == SDL_EVENT_KEY_DOWN) {
        switch (event->key.key) {
            case SDLK_W: player->cordY -= 15; break;
            case SDLK_A: player->cordX -= 15; break;
            case SDLK_S: player->cordY += 15; break;
            case SDLK_D: player->cordX += 15; break;

            case SDLK_ESCAPE: running = false; break;
        }
    }

}


inline void R1_AppQuit() {

    for (auto obj : M_RenderableList) {
        delete obj;
    }
    M_RenderableList.clear();
    SDL_Log("[R1] [SDL_AppQuit]: Cleaned up M_RenderableList");

    for (auto& tex : M_TexturesList) {
        if (tex) {
            SDL_DestroyTexture(tex);
            tex = nullptr;
        }
    }
    M_TexturesList.clear();
    SDL_Log("[R1] [SDL_AppQuit]: Cleaned up M_TexturesList");

}

#endif