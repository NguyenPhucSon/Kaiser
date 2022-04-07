#include <iostream>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include "basic_variables.h"
#include "Media.h"
#include "collapse.h"

using namespace std;

struct Button
{
    int value;
    bool revealable;
    bool markable;
};

int mineField [40][40];
Button mineMap [40][40];

int checkAround(int x, int y)
{
    int s = 0;
    for (int k=0; k<8; k++){
        int j = x + xCor[k];
        int i = y + yCor[k];
        if ( i<0 || j<0 || i>=h || j>=w ) continue;
        else{
            if (mineField[i][j] == 1) s++;
        }
    }
    return s;
}

void Setup()
{
    endGame = false;
    onScreen = false;
    isWin = false;
    actualMineRemain = mine;
    mineRemain = mine;
    nof = 0;
    for (int i=0; i<h; i++){
        for (int j = 0; j<w; j++){
            mineField[i][j] = 0;
        }
    }
    int x = 0;
    int y = 0;
    srand(time(NULL));
    for (int i=0; i<mine; i++){
        do{
            x = rand() % (w - 1) + 0;
            y = rand() % (h - 1) + 0;
        } while (mineField [x][y] != 0);
        mineField[x][y] = 1;
    }
}

void createMap()
{
    for (int i=0; i<h; i++) {
        for (int j=0; j<w; j++){
            if (mineField[i][j] == 0){
                mineMap[i][j].value = checkAround(j, i);
            } else {
                mineMap[i][j].value = -1;
            }
            mineMap[i][j].markable = true;
            mineMap[i][j].revealable = true;
        }
    }
}

void loadGame() {
    Setup();
    createMap();

    int initX = (gWindow.getWidth() - 32 * w) / 2;
    int initY = (gWindow.getHeight() - 32 * h) / 2;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            gSpriteSheetTexture.render(initX + j*32, initY + i*32, &gSpriteClips[10]);
        }
    }

    SDL_SetRenderDrawColor( gRenderer, 111, 143, 175, 0xFF );
    infor.render((gWindow.getWidth() - infor.getWidth()) / 2, initY - infor.getHeight() - 10);
    displayCounting.render((gWindow.getWidth() - 28) / 2, initY - infor.getHeight() - 1, &displayMineRemain[mineRemain / 10]);
    displayCounting.render((gWindow.getWidth() - 28) / 2 + 14, initY - infor.getHeight() - 1, &displayMineRemain[mineRemain % 10]);
    SDL_RenderPresent(gRenderer);
}

void gameOver() {
    int initX = (gWindow.getWidth() - 32 * w) / 2;
    int initY = (gWindow.getHeight() - 32 * h) / 2;
    mineRemain = 0;
    SDL_SetRenderDrawColor(gRenderer, 111, 143, 175, 0xFF);

    for (int i = 0; i<h; i++) {
        for (int j = 0; j<w; j++) {
            if (mineMap[i][j].value == -1) {
                gSpriteSheetTexture.render(initX+j*32, initY+i*32, &gSpriteClips[9]);
            } else {
                if (mineMap[i][j].revealable) {
                    if (mineMap[i][j].markable) {
                        gSpriteSheetTexture.render(initX+j*32, initY+i*32, &gSpriteClips[10]);
                    } else {
                        gSpriteSheetTexture.render(initX+j*32, initY+i*32, &gSpriteClips[11]);
                    }
                } else {
                    int m = mineMap[i][j].value;
                    gSpriteSheetTexture.render(initX+j*32, initY+i*32, &gSpriteClips[m]);
                }
            }
        }
    }

    infor.render((gWindow.getWidth() - infor.getWidth()) / 2, initY - infor.getHeight() - 10);
    displayCounting.render((gWindow.getWidth() - 28) / 2, initY - infor.getHeight() - 1, &displayMineRemain[mineRemain / 10]);
    displayCounting.render((gWindow.getWidth() - 28) / 2 + 14, initY - infor.getHeight() - 1, &displayMineRemain[mineRemain % 10]);
    SDL_RenderPresent(gRenderer);
    endGame = true;
}


void loadScreen() {
    int initX = (gWindow.getWidth() - 32 * w) / 2;
    int initY = (gWindow.getHeight() - 32 * h) / 2;
    SDL_SetRenderDrawColor(gRenderer, 111, 143, 175, 0xFF);
    SDL_RenderClear( gRenderer );

    infor.render((gWindow.getWidth() - infor.getWidth()) / 2, initY - infor.getHeight() - 10);

    if (!endGame) {
        if (mineRemain >=0) {
            displayCounting.render((gWindow.getWidth() - 28) / 2, initY - infor.getHeight() - 1, &displayMineRemain[mineRemain / 10]);
            displayCounting.render((gWindow.getWidth() - 28) / 2 + 14, initY - infor.getHeight() - 1, &displayMineRemain[mineRemain % 10]);
        } else {
            displayCounting.render((gWindow.getWidth() - 28) / 2, initY - infor.getHeight() - 1, &displayMineRemain[0]);
            displayCounting.render((gWindow.getWidth() - 28) / 2 + 14, initY - infor.getHeight() - 1, &displayMineRemain[0]);
        }
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (mineMap[i][j].revealable) {
                    if (mineMap[i][j].markable) {
                        gSpriteSheetTexture.render(initX + j*32, initY + i*32, &gSpriteClips[10]);
                    } else {
                        gSpriteSheetTexture.render(initX + j*32, initY + i*32, &gSpriteClips[11]);
                    }
                } else {
                    int m = mineMap[i][j].value;
                    gSpriteSheetTexture.render(initX + j*32, initY + i*32, &gSpriteClips[m]);
                }
            }
        }
        SDL_RenderPresent(gRenderer);
    } else {
        gameOver();
    }
}

void reveal(int x, int y)
{
    int initX = (gWindow.getWidth() - 32 * w) / 2;
    int initY = (gWindow.getHeight() - 32 * h) / 2;
    if (mineMap[y][x].revealable){
        if (mineMap[y][x].markable){
            int m = mineMap[y][x].value;
            if (m==-1){
                Mix_PlayChannel(-1, gScratch, 0);
                gameOver();
            }
            else if (m>0){
                gSpriteSheetTexture.render(initX+x*32, initY+y*32, &gSpriteClips[m]);
                mineMap[y][x].revealable = false;
            }
            else {
                gSpriteSheetTexture.render(initX+x*32, initY+y*32, &gSpriteClips[0]);
                mineMap[y][x].revealable = false;
                for (int k=0; k<8; k++){
                    int i = y + yCor[k];
                    int j = x + xCor[k];
                    if (i<0 || j<0 || i>=h || j>=w){
                        continue;
                    }
                    else{
                        reveal(j, i);
                    }
                }
            }
        }
    }
}

void mark(int x, int y)
{
    int initX = (gWindow.getWidth() - 32 * w) / 2;
    int initY = (gWindow.getHeight() - 32 * h) / 2;
    if (mineMap[y][x].revealable){
        if (mineMap[y][x].markable){
            gSpriteSheetTexture.render(initX+x*32, initY+y*32, &gSpriteClips[11]);
            mineMap[y][x].markable = false;
            mineRemain--;
            if (mineMap[y][x].value == -1) {
                actualMineRemain--;
            }
        }
        else {
            gSpriteSheetTexture.render(initX+x*32, initY+y*32, &gSpriteClips[10]);
            mineMap[y][x].markable = true;
            mineRemain++;
            if (mineMap[y][x].value == -1) {
                actualMineRemain++;
            }
        }
    }
}

void replay()
{
    int initX = (gWindow.getWidth() - 32 * w) / 2;
    int initY = (gWindow.getHeight() - 32 * h) / 2;
    Setup();
    createMap();
    for (int i=0; i<h; i++) {
        for (int j = 0; j<w; j++) {
            gSpriteSheetTexture.render(initX+j*32, initY+i*32, &gSpriteClips[10]);
        }
    }
    infor.render((gWindow.getWidth() - infor.getWidth()) / 2, initY - infor.getHeight() - 10);
    displayCounting.render((gWindow.getWidth() - 28) / 2, initY - infor.getHeight() - 5, &displayMineRemain[mineRemain / 10]);
    displayCounting.render((gWindow.getWidth() - 28) / 2 + 14, initY - infor.getHeight() - 5, &displayMineRemain[mineRemain % 10]);

    SDL_RenderPresent(gRenderer);
}

int main( int argc, char* args[] )
{
    int width = SCREEN_WIDTH;
    int height = SCREEN_HEIGHT;
    posX = -1;
    posY = -1;
    isPlaying = false;
	if( !init() ) {
		printf( "Failed to initialize!\n" );
	} else {
		if( !loadMedia() ) {
			printf( "Failed to load media!\n" );
		} else {
			bool quit = false;

			SDL_Event e;

			while( !quit ) {

			    if (actualMineRemain == 0 && nof == 0 && isPlaying && onScreen && mineRemain == 0) {
                    Mix_PlayChannel(-1, gBeat, 0);
                    nof = 1;
                    isWin = true;
			    }

			    int minX = (gWindow.getWidth() - gSceneTexture.getWidth()) / 2 + 240;;
                int maxX = minX + 90;
                int minY = (gWindow.getHeight() - gSceneTexture.getHeight()) / 2 + 234;

				while( SDL_PollEvent( &e ) != 0 ) {
					if( e.type == SDL_QUIT ) {
						quit = true;
					}

					gWindow.handleEvent( e );

					if (e.type == SDL_MOUSEMOTION) {
                        posX = e.motion.x;
                        posY = e.motion.y;

					}

					if (e.type == SDL_MOUSEBUTTONDOWN && !isPlaying) {
                        if (e.button.button == SDL_BUTTON_LEFT) {
                            if (posX < maxX && posX > minX) {
                                if ( minY < posY && posY < minY + 28) {
                                    w = 8;
                                    h = 8;
                                    mine = 10;
                                    width = 600;
                                    height = 400;
                                    gWindow.setWindowSize(width, height);
                                    isPlaying = true;
                                }
                                if (minY + 28 + 2 < posY && posY < minY + 28*2 + 2) {
                                    w = 16;
                                    h = 16;
                                    mine = 40;
                                    width = 1000;
                                    height = 640;
                                    gWindow.setWindowSize(width, height);
                                    isPlaying = true;
                                }
                                if (minY + 28*2 + 4 < posY && posY < minY + 28*3 + 6) {
                                    w = 25;
                                    h = 20;
                                    mine = 99;
                                    gWindow.setWindowMaximize();
                                    isPlaying = true;
                                }
                            }
                        }
					}

					if (isPlaying && onScreen) {
                        int initX = (gWindow.getWidth() - 32 * w) / 2;
                        int initY = (gWindow.getHeight() - 32 * h) / 2;
                        int x, y;

                        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                            isPlaying = false;
                            onScreen = false;
                            gWindow.setWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
                            gWindow.restoreWIndow();
                            SDL_RenderClear(gRenderer);
                            gSceneTexture.render((gWindow.getWidth() - gSceneTexture.getWidth()) / 2, (gWindow.getHeight() - gSceneTexture.getHeight()) / 2);
                            SDL_RenderPresent(gRenderer);
                        } else if (e.type == SDL_MOUSEBUTTONDOWN && isPlaying) {
                            if (posX > initX && posY > initY) {
                                x = (posX - initX) / 32;
                                y = (posY - initY) / 32;
                            } else {
                                x = -1;
                                y = -1;
                            }
                            int replayPosX = (gWindow.getWidth() - infor.getWidth()) / 2 + 200;
                            int replayPosY = initY - infor.getHeight() + 5;

                            if (0 <= x && x < w && 0 <= y && y < h && (!endGame) && (!isWin)) {
                                Mix_PlayChannel(-1, gClick, 0);
                                if (e.button.button == SDL_BUTTON_LEFT) {
                                    reveal(x, y);
                                }
                                if (e.button.button == SDL_BUTTON_RIGHT) {
                                    mark(x, y);
                                }
                                SDL_RenderPresent(gRenderer);
                            } else if (replayPosX < posX && posX < replayPosX + 20) {
                                if (replayPosY < posY && posY < replayPosY + 20) {
                                    replay();
                                }
                            }
                        }
                    }
				}

				if (isPlaying && (!onScreen)) {
                    SDL_RenderClear(gRenderer);
                    loadGame();
                    onScreen = true;
				}

				if(!gWindow.isMinimized()) {
					if (!isPlaying) {
                        SDL_SetRenderDrawColor(gRenderer, 70, 130, 180, 0xFF);
                        SDL_RenderClear( gRenderer );

                        gSceneTexture.render((gWindow.getWidth() - gSceneTexture.getWidth()) / 2, (gWindow.getHeight() - gSceneTexture.getHeight()) / 2);

                        SDL_RenderPresent( gRenderer );
					} else {
                        loadScreen();
					}
				}
			}
		}
	}
	close();
	return 0;
}
