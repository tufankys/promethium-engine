#ifndef MAINLIB_HPP
#define MAINLIB_HPP

//libs
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

//definitions
extern SDL_Window* window;
extern SDL_Renderer* renderer;

class M_Renderable;

inline std::vector<M_Renderable*> M_RenderableList = {};
inline std::vector<SDL_Texture*> M_TexturesList = {};
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


//TextObject Class
class M_TextObject : public M_Renderable {
public:
    std::string text;
    SDL_Texture* fontAtlas; // grid
    int charWidth;          // 16
    int charHeight;         // 16

    M_TextObject(int inputX, int inputY, int inputW, int inputH, 
                 SDL_Texture* inputFont, std::string inputText)
        : M_Renderable(inputX, inputY, inputW, inputH), 
          fontAtlas(inputFont), text(inputText) {
        
        // Varsayılan karakter boyutları (Grid yapına göre bunları ayarla)
        charWidth = 16; 
        charHeight = 16;
    }

    void render(SDL_Renderer* iRenderer) override {
        if (!willRender || !fontAtlas) return;

        updateRect();

        int charsPerRow = 16; // PNG'deki bir satırda bulunan karakter sayısı

        for (size_t i = 0; i < text.length(); ++i) {
            // 1. Karakterin ASCII değerini al
            int ascii = (unsigned char)text[i];
            
            // Eğer atlasın 32. karakterden (Space) başlıyorsa ofset ekle:
            // int index = ascii - 32; 
            int index = ascii - 32; 

            // 2. Kaynak (Source) Koordinatları: Grid üzerindeki yer
            SDL_FRect src_rect;
            src_rect.x = (float)((index % charsPerRow) * charWidth);
            src_rect.y = (float)((index / charsPerRow) * charHeight);
            src_rect.w = (float)charWidth;
            src_rect.h = (float)charHeight;

            // 3. Hedef (Destination) Koordinatları: Ekranda nereye çizilecek?
            // Her karakteri i kadar sağa kaydırıyoruz
            SDL_FRect char_dst_rect;
            char_dst_rect.x = dst_rect.x + (i * (dst_rect.w / text.length())); // Basit ölçekleme
            char_dst_rect.y = dst_rect.y;
            char_dst_rect.w = (float)(dst_rect.w / text.length()); // Harf genişliği
            char_dst_rect.h = dst_rect.h;

            // Çizim yap
            SDL_RenderTexture(iRenderer, fontAtlas, &src_rect, &char_dst_rect);
        }
    }
};
//






//functions
inline SDL_Texture *M_LoadTexture(SDL_Renderer* iRenderer, const char* filename) {
    SDL_Texture* newTexture = nullptr;
    char *full_path = nullptr;

    if (SDL_asprintf(&full_path, "%s..\\sprites\\%s", SDL_GetBasePath(), filename) <= 0) {
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
    SDL_Log("[M_CreateTextureObject]: Creating object: %s", filename);
    return new M_TextureObject(x, y, w, h, M_FindTexture(filename));
}

inline M_TextObject* M_CreateTextObject(int x, int y, int w, int h, const char* fontFilename, const std::string& text) {
    SDL_Log("[M_CreateTextObject]: Creating text object with font: %s", fontFilename);
    SDL_Texture* fontAtlas = M_FindTexture(fontFilename);
    
    if (!fontAtlas) {
        SDL_Log("[M_CreateTextObject] ERROR: Font texture could not be found or loaded: %s", fontFilename);
        return nullptr;
    }

    return new M_TextObject(x, y, w, h, fontAtlas, text);
}

inline void M_SetDrawColor(SDL_Renderer *iRenderer, int r, int g, int b) {
     SDL_SetRenderDrawColor(iRenderer, r, g, b, SDL_ALPHA_OPAQUE);
}

inline void M_RenderDebugText(SDL_Renderer *iRenderer, int x, int y, const char* text) {
    SDL_RenderDebugText(iRenderer, x, y, text );
}


#endif //MAINLIB_HPP