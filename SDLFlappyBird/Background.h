#pragma once
#include "SpriteHandler.h"

class Background
{
public:
	Background();
	Background(SDL_Renderer* renderer, TextureLoader tl, int windowWidth, int windowHeight);
	void Render(SDL_Renderer* rendererer, bool animate);

private:

	SpriteHandler backgroundSprite;
	SpriteHandler treesSprite;
	SpriteHandler treesbgSprite;
	SpriteHandler cloudSprite;
	SpriteHandler starsSprite;

	SDL_Rect loopPlane{0,0,0,0};
	SDL_Rect treePlane{ 0,0,0,0 };
	SDL_Rect treebgPlane{ 0,0,0,0 };
	SDL_Rect cloudPlane{ 0,0,0,0 };
	SDL_Rect moonPlane{ 0,0,0,0 };
	SDL_Rect starsPlane{ 0,0,0,0 };
	SDL_Rect effectPlane{ 0,0,0,0 };

	SDL_Texture* background=nullptr;
	SDL_Texture* starsLoop = nullptr;
	SDL_Texture* moon = nullptr;
	SDL_Texture* bgLoop = nullptr;
	SDL_Texture* treesLoop = nullptr;
	SDL_Texture* treesbgLoop = nullptr;
	SDL_Texture* cloudLoop = nullptr;
	SDL_Texture* moonEffect = nullptr;
};

