#ifndef MAINLIB_HPP
#define MAINLIB_HPP

//libs
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

//definitions
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define WINDOW_NAME "Promethium Engine"
#define TEXT_SIZE 33
#define TEXT_COLOR (SDL_Color){255,255,255,255}

inline SDL_Window* window = nullptr;
inline SDL_Renderer* renderer = nullptr;
inline TTF_Font* font = nullptr;

inline bool running = true;

class M_Renderable;
class M_TextureObject;
class M_TextObject;

inline std::vector<M_Renderable*> M_RenderableList = {};
inline std::vector<SDL_Texture*> M_TexturesList = {};


SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]);
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event);
SDL_AppResult SDL_AppIterate(void *appstate);
void SDL_AppQuit(void *appstate, SDL_AppResult result);


//


//classes
//Renderable Class
class M_Renderable {
public:
    int cordX, cordY, width, height;
    bool willRender = true;
    SDL_FRect dst_rect;
    
    M_Renderable(int inputX, int inputY, int inputW, int inputH)
        : cordX(inputX), cordY(inputY), width(inputW), height(inputH) {
        updateRect();
        M_RenderableList.push_back(this);
    }

    virtual void render(SDL_Renderer* iRenderer) = 0;

    void updateRect() { dst_rect.x = (float) cordX; dst_rect.y = (float) cordY; dst_rect.w = (float) width; dst_rect.h = (float) height;  }

    virtual ~M_Renderable() {}
};


//TextureObject Class
class M_TextureObject : public M_Renderable {
public:
    SDL_Texture* texture;

    M_TextureObject(int inputX, int inputY, int inputW, int inputH, SDL_Texture* inputTexture)
        : M_Renderable(inputX, inputY, inputW, inputH), texture(inputTexture) {}
    
    void render(SDL_Renderer *iRenderer) override {
        if (willRender) { 
            updateRect(); 
            SDL_RenderTexture(iRenderer, texture, nullptr, &dst_rect); 
        }
    }

};

//TextureObject Class
class M_TextObject{
public:
    SDL_Texture* texture;
    SDL_FRect dst_rect;
    bool willRender = true;

    M_TextObject(SDL_Renderer* iRenderer, int inputX, int inputY, const char* iText) {
        SDL_Surface* surface = TTF_RenderText_Blended(font, iText, 0, TEXT_COLOR);

        if (!surface) {
                SDL_Log("[!M_TextObject]: Could not create surface (%s): %s", iText, SDL_GetError());
            } else {
                texture = SDL_CreateTextureFromSurface(iRenderer, surface);
                if (!texture) {
                    SDL_Log("[!M_TextObject]: Could not create texture from surface (%s): %s", iText, SDL_GetError());
                } else {
                    //SDL_SetStringProperty(SDL_GetTextureProperties(newTexture), "name", filename);
                    //M_TexturesList.push_back(newTexture);
                    dst_rect.w = surface->w;
                    dst_rect.h = surface->h;
                    SDL_Log("[M_TextObject]: Created texture: %s", iText);
            }
            SDL_DestroySurface(surface);
            }
        }
        
    void render(SDL_Renderer* iRenderer) {
        SDL_RenderTexture(iRenderer, texture, nullptr, &dst_rect); 
    }

};

//






//functions
inline SDL_Texture *M_LoadTexture(SDL_Renderer* iRenderer, const char* filename) {
    SDL_Texture* newTexture = nullptr;
    char *full_path = nullptr;

    if (SDL_asprintf(&full_path, "%s..\\assets\\sprites\\%s", SDL_GetBasePath(), filename) <= 0) {
        SDL_Log("[!M_LoadTexture]: Path string creation failed for: %s , %s", filename, SDL_GetError());
        return nullptr;
    }

    SDL_Surface* surface = SDL_LoadPNG(full_path);
    
    if (!surface) {
        SDL_Log("[!M_LoadTexture]: Could not load surface (%s): %s", full_path, SDL_GetError());
    } else {
        newTexture = SDL_CreateTextureFromSurface(iRenderer, surface);
        if (!newTexture) {
            SDL_Log("[!M_LoadTexture]: Could not create texture (%s): %s", filename, SDL_GetError());
        } else {
            SDL_SetStringProperty(SDL_GetTextureProperties(newTexture), "name", filename);
            M_TexturesList.push_back(newTexture);
            SDL_Log("[M_LoadTexture]: Loaded texture: %s", filename);
        }
        SDL_DestroySurface(surface);
    }

    SDL_free(full_path);
    
    return newTexture;
}


inline SDL_Texture* M_FindTexture(const char* filename) {
    for (SDL_Texture* tex : M_TexturesList) {
        if (tex) {
            const char* texName = SDL_GetStringProperty(SDL_GetTextureProperties(tex), "name", NULL);
            
            if (texName && SDL_strcmp(texName, filename) == 0) {
                return tex;
            }
        }
    }
    
    SDL_Log("[!M_FindTexture]: Texture not found: %s", filename);
    return nullptr;
}

inline M_TextureObject* M_CreateTextureObject(int x, int y, int w, int h, const char* filename) {
    SDL_Log("[M_CreateTextureObject]: Creating TEXTURE object: %s", filename);
    return new M_TextureObject(x, y, w, h, M_FindTexture(filename));
}

inline M_TextObject* M_CreateTextObject(SDL_Renderer* iRenderer,int x, int y, const char* iText) {
    SDL_Log("[M_CreateTextObject]: Creating TEXT object: %s", iText);
    return new M_TextObject(iRenderer, x, y, iText);
}


inline void M_SetDrawColor(SDL_Renderer *iRenderer, int r, int g, int b) {
     SDL_SetRenderDrawColor(iRenderer, r, g, b, SDL_ALPHA_OPAQUE);
}

inline void M_RenderDebugText(SDL_Renderer *iRenderer, int x, int y, const char* text) {
    SDL_RenderDebugText(iRenderer, x, y, text );
}


#endif //MAINLIB_HPP