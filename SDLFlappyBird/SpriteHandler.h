#pragma once
#include "SDL.h"
#include "TextureLoader.h"

class SpriteHandler
{
public:
	SpriteHandler();
	SpriteHandler(SDL_Texture* tex,int flag,SDL_Rect& objectRect,int loopSize,int stepLength);
	bool Finished();
	void Render(SDL_Renderer* renderer,SDL_Rect& dstRect, float rotation, bool animate);
	void Reset();
private:
	SDL_Texture* sprite=nullptr;
	SDL_Rect renderRect;
	TextureLoader spriteLoader;
	SDL_Point spriteSize;

	int loopSize=0;
	int flag = 0;
	float stepSize = 0;
	float currentStep = 0;
};