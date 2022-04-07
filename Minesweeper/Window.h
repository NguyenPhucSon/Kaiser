#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include "const.h"

class LWindow
{
	public:
		LWindow() {
            mWindow = NULL;
            mFullScreen = false;
            mMinimized = false;
            mWidth = 0;
            mHeight = 0;
		}

		bool init() {
            mWindow = SDL_CreateWindow("Minesweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
            if(mWindow != NULL) {
                mWidth = SCREEN_WIDTH;
                mHeight = SCREEN_HEIGHT;
            }
            return mWindow != NULL;
		}

		void free() {
            if(mWindow != NULL) {
                SDL_DestroyWindow( mWindow );
            }
            mWidth = 0;
            mHeight = 0;
		}

		SDL_Renderer* createRenderer() {
			return SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		}

		void handleEvent(SDL_Event& e) {
            if( e.type == SDL_WINDOWEVENT )
            {
                switch(e.window.event)
                {
                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                        mWidth = e.window.data1;
                        mHeight = e.window.data2;
                        break;

                    case SDL_WINDOWEVENT_EXPOSED:
                        SDL_RenderPresent(gRenderer);
                        break;

                    case SDL_WINDOWEVENT_MINIMIZED:
                        mMinimized = true;
                        break;

                    case SDL_WINDOWEVENT_MAXIMIZED:
                        mMinimized = false;
                        break;

                    case SDL_WINDOWEVENT_RESTORED:
                        mMinimized = false;
                        break;
                }
            }
            else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_F11)
            {
                if(mFullScreen)
                {
                    SDL_SetWindowFullscreen( mWindow, SDL_FALSE );
                    mFullScreen = false;
                }
                else
                {
                    SDL_SetWindowFullscreen(mWindow, SDL_TRUE);
                    mFullScreen = true;
                    mMinimized = false;
                }
            }
		}

		int getWidth() {
            return mWidth;
        }
		int getHeight() {
            return mHeight;
        }

		void setWindowSize(int width, int height) {
		    SDL_SetWindowSize(mWindow, width, height);
		}
		void setWindowMaximize() {
            SDL_MaximizeWindow(mWindow);
		}
		void restoreWIndow() {
		    SDL_RestoreWindow(mWindow);
		}

		bool isMinimized() {
            return mMinimized;
		}

	private:
		SDL_Window* mWindow;

		int mWidth;
		int mHeight;

		bool mFullScreen;
		bool mMinimized;
};

#endif // WINDOW_H_INCLUDED
