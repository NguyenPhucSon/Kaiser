#ifndef MEDIA_H_INCLUDED
#define MEDIA_H_INCLUDED

#include "advanced_variables.h"

bool init() {
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	} else {
		if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" )) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		if( !gWindow.init() ) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		} else {
			gRenderer = gWindow.createRenderer();
			if( gRenderer == NULL ) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			} else {
				SDL_SetRenderDrawColor(gRenderer, 115, 147, 179, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if( !(IMG_Init(imgFlags) & imgFlags) ) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				int jpgFlags = IMG_INIT_JPG;
				if (!(IMG_Init( jpgFlags) & jpgFlags)) {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
                }
                if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0) {
                    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                    success = false;
                }
			}
		}
	}
	return success;
}

bool loadMedia()
{
	bool success = true;

	if(!gSceneTexture.loadFromFile( "res/image/template1.png")) {
		printf( "Failed to load window texture! \n" );
		success = false;
	}

	if (!gSpriteSheetTexture.loadFromFile("res/image/Tiles.png")) {
        printf( "Failed to load spirite sheet from texture \n");
        success = false;
    } else {
        for (int i = 0; i<12; i++){
            gSpriteClips[i].x = 32*i;
            gSpriteClips[i].y = 0;
            gSpriteClips[i].w = 32;
            gSpriteClips[i].h = 32;
        }
    }

    if (!infor.loadFromFile("res/image/infobar.png")) {
        printf("Failed to load info bar \n");
        success = false;
    }

    if (!displayCounting.loadFromFile("res/image/Count2.png")) {
        printf("Failed to counting \n");
        success = false;
    } else {
        for (int i = 0; i<10; i++) {
            displayMineRemain[i].x = 14*i;
            displayMineRemain[i].y = 0;
            displayMineRemain[i].w = 14;
            displayMineRemain[i].h = 23;
        }
    }

    gBeat = Mix_LoadWAV("res/sound/beat.wav");
	if(gBeat == NULL) {
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gClick = Mix_LoadWAV("res/sound/click.wav");
	if(gClick == NULL) {
		printf("Failed to load click music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gScratch = Mix_LoadWAV( "res/sound/scratch2.wav" );
	if( gScratch == NULL ) {
		printf("Failed to load scratch music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	return success;
}

#endif // MEDIA_H_INCLUDED
