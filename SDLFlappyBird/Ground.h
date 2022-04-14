#pragma once
#include "SDL.h"
#include "SpriteHandler.h"

class Ground
{
public:
	SDL_Rect Hitbox;

	Ground();
	Ground(SDL_Renderer* renderer,TextureLoader& tl,int height,int width);

	void Render(SDL_Renderer* renderer, bool animate,bool showGrid);
private:
	SDL_Texture* texture;
	SpriteHandler groundSprite;
};