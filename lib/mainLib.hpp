#ifndef MAINLIB_HPP
#define MAINLIB_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern std::vector<SDL_Texture*> textures;


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



extern M_TextureObject player;



inline SDL_Texture *M_LoadTexture(SDL_Renderer* renderer, const char* filename) {
    SDL_Texture* newTexture = NULL;
    char *full_path = NULL;

    if (SDL_asprintf(&full_path, "%s..\\sprites\\%s", SDL_GetBasePath(), filename) <= 0) {
        SDL_Log("[!M_LoadTexture]: Path string creation failed for: %s , %s", filename, SDL_GetError());
        return NULL;
    }

    SDL_Surface* surface = SDL_LoadPNG(full_path);
    
    if (!surface) {
        SDL_Log("[!M_LoadTexture]: Could not load surface (%s): %s", full_path, SDL_GetError());
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!newTexture) {
            SDL_Log("[!M_LoadTexture]: Could not create texture (%s): %s", filename, SDL_GetError());
        } else {
            SDL_SetStringProperty(SDL_GetTextureProperties(newTexture), "name", filename);
            textures.push_back(newTexture);
            SDL_Log("[M_LoadTexture]: Loaded texture: %s", filename);
        }
        SDL_DestroySurface(surface);
    }

    SDL_free(full_path);
    
    return newTexture;
}

inline SDL_Texture* M_FindTexture(const char* filename) {
    for (SDL_Texture* tex : textures) {
        if (tex) {
            const char* texName = SDL_GetStringProperty(SDL_GetTextureProperties(tex), "name", NULL);
            
            if (texName && SDL_strcmp(texName, filename) == 0) {
                return tex;
            }
        }
    }
    
    SDL_Log("[!M_FindTexture]: Texture not found: %s", filename);
    return NULL;
}

inline void M_SetDrawColor(SDL_Renderer *renderer, int r, int g, int b) {
     SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
}

inline void M_RenderDebugText(SDL_Renderer *renderer, int x, int y, const char* text) {
    SDL_RenderDebugText(renderer, x, y, text );
}


#endif // MAINLIB_HPP