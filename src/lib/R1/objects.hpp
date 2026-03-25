#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include "..\\mainLib.hpp"

inline M_TextureObject* player = nullptr;
inline M_TextObject* testText = nullptr;

inline void R1_loadTextures() {
    M_LoadTexture(renderer, "sample.png");
}

inline void R1_createObjects() {
    player = M_CreateTextureObject(320, 240, 90, 90 , "sample.png");
    testText = new M_TextObject(renderer, 0, 0, "YARRAK");
}


#endif