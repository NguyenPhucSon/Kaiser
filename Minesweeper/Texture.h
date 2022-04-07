#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>

SDL_Renderer* gRenderer = NULL;

class LTexture
{
    public:
        LTexture() {
            mWidth = 0;
            mHeight = 0;
            mTexture = NULL;
        }

        void Free() {
            if (mTexture != NULL) {
                SDL_DestroyTexture(mTexture);
                mTexture = NULL;
                mWidth = 0;
                mHeight = 0;
            }
        }

        ~LTexture() {
            Free();
        }

        bool loadFromFile (std::string path) {
            Free();

            SDL_Texture* newTexture = NULL;

            SDL_Surface* loadedSurface = IMG_Load(path.c_str());
            if (loadedSurface == NULL) {
                //cout<<"Unable to load surface. ERROR: \n"<<IMG_GetError()<<endl;
                printf( "Unable to load surface! SDL_Error: %s\n", SDL_GetError() );
            } else {
                newTexture = SDL_CreateTextureFromSurface (gRenderer, loadedSurface);
            }
            if (newTexture == NULL) {
                printf( "Unable to create texture from surface! SDL_Error: %s\n", SDL_GetError() );
            } else {
                mWidth = loadedSurface->w;
                mHeight = loadedSurface->h;
            }
            mTexture = newTexture;
            return mTexture!=NULL;
        }

        void render (int x, int y, SDL_Rect* Clips = NULL) {
            SDL_Rect renderQuad = {x, y, mWidth, mHeight};
            if (Clips != NULL) {
                renderQuad.w = Clips->w;
                renderQuad.h = Clips ->h;
            }
            SDL_RenderCopy (gRenderer, mTexture, Clips, &renderQuad);
        }

        int getWidth() {
            return mWidth;
        }
        int getHeight() {
            return mHeight;
        }

    private:
        SDL_Texture* mTexture;
        int mWidth;
        int mHeight;

};

#endif // TEXTURE_H_INCLUDED
