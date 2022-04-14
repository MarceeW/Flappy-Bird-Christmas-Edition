#include "TextureLoader.h"

TextureLoader::TextureLoader() {
	IMG_Init(IMG_INIT_PNG);
}
SDL_Texture* TextureLoader::LoadTexture (SDL_Renderer* renderer,const char* dest) {
	SDL_Surface* surf = IMG_Load(dest);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	return tex;
}
