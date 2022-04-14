#pragma once
#include "SDL.h"
#include "SDL_image.h"

class TextureLoader
{
public:
	TextureLoader();

	SDL_Texture* LoadTexture(SDL_Renderer* renderer,const char* dest);
};

