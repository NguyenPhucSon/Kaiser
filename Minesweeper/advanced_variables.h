#ifndef ADVANCED_VARIABLES_H_INCLUDED
#define ADVANCED_VARIABLES_H_INCLUDED

#include <SDL_mixer.h>
#include "Texture.h"
#include "Window.h"

using namespace std;

Mix_Chunk *gScratch = NULL;
Mix_Chunk *gClick = NULL;
Mix_Chunk *gBeat = NULL;

LWindow gWindow;

LTexture gSceneTexture;
LTexture infor;

LTexture gSpriteSheetTexture;
SDL_Rect gSpriteClips[12];

LTexture displayCounting;
SDL_Rect displayMineRemain[10];

#endif // ADVANCED_VARIABLES_H_INCLUDED
