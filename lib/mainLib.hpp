#ifndef MAINLIB_HPP
#define MAINLIB_HPP

#include <string>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

class M_TextureObject {
private:
    SDL_FRect dst_rect;
public:
    int x;
    int y;
    int w;
    int h;

    M_TextureObject(int inputX, int inputY, int inputW, int inputH) {
        x = inputX;
        y = inputY;
        w = inputW;
        h = inputH;

        dst_rect.x = (float) x;
        dst_rect.y = (float) y;
        dst_rect.w = (float) w;
        dst_rect.h = (float) h;
    }

    void render(SDL_Renderer *renderer, SDL_Texture *texture) {
        dst_rect.x = (float) x;
        dst_rect.y = (float) y;
        dst_rect.w = (float) w;
        dst_rect.h = (float) h;
        SDL_RenderTexture(renderer, texture, NULL, &dst_rect);
    }

};

inline void M_LoadTexture() {
    //TODO
}

inline void M_SetDrawColor(SDL_Renderer *renderer, int r, int g, int b) {
     SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
}

inline void M_RenderDebugText(SDL_Renderer *renderer, int x, int y, const char* text) {
    SDL_RenderDebugText(renderer, x, y, text );
}


#endif // MAINLIB_HPP