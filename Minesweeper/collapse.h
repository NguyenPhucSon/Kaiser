#ifndef COLLAPSE_H_INCLUDED
#define COLLAPSE_H_INCLUDED

#include "advanced_variables.h"

void close() {
	gSceneTexture.Free();
	gSpriteSheetTexture.Free();
	infor.Free();
	displayCounting.Free();

	SDL_DestroyRenderer( gRenderer );
	gWindow.free();

	Mix_FreeChunk(gScratch);
    	Mix_FreeChunk(gBeat);
    	Mix_FreeChunk(gClick);
    	gClick = NULL;
    	gBeat = NULL;
    	gScratch = NULL;

	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

#endif // COLLAPSE_H_INCLUDED
