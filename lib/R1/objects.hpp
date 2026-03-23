#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include "..\\app.hpp"

inline M_TextureObject* player = nullptr;
inline M_TextObject* testText = nullptr;

inline void loadTextures() {
    M_LoadTexture(renderer, "sample.png");
    M_LoadTexture(renderer, "grid.png");
}

inline void createObjects() {
    player = M_CreateTextureObject(320, 240, 90, 90 , "sample.png");
    testText = M_CreateTextObject(32, 32, 260, 16, "grid.png", "hell");
}


#endif