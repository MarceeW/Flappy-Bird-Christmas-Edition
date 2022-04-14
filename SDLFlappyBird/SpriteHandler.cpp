#include "SpriteHandler.h"

SpriteHandler::SpriteHandler(){}

SpriteHandler::SpriteHandler(SDL_Texture* tex, int flag,SDL_Rect& objectRect,int loopSize, int stepLength) {
	sprite = tex;
	this->flag = flag;
	this->loopSize = loopSize;
	
	SDL_QueryTexture(tex, NULL, NULL, &spriteSize.x, &spriteSize.y);

	if (!flag)
	{
		renderRect = objectRect;
		renderRect.w += loopSize;
	}
	else {
		renderRect.x = 0;
		renderRect.y = 0;
		renderRect.w = loopSize ? loopSize : spriteSize.y;
		renderRect.h = spriteSize.y;
	}

	if (flag) {
		stepSize = (float)renderRect.h / (float)stepLength;
	}
	else {
		stepSize= (float)loopSize / (float)stepLength;
	}
}
void SpriteHandler::Reset() {
	currentStep = 0;
	renderRect.x = 0;
}
bool SpriteHandler::Finished() {
	return renderRect.x+renderRect.w == spriteSize.x;
}
void SpriteHandler::Render(SDL_Renderer* renderer, SDL_Rect& dstRect,float rotation,bool animate) {
	
	if (flag) {
		if (currentStep >= renderRect.w) {
			renderRect.x += renderRect.w;
			currentStep = 0;
		}
		if (renderRect.x >= spriteSize.x)
			renderRect.x = 0;
		if (rotation > 0) {
			SDL_RenderCopyEx(renderer, sprite, &renderRect, &dstRect, rotation, NULL, SDL_FLIP_NONE);
		}
		else {
			SDL_RenderCopy(renderer, sprite, &renderRect, &dstRect);
		}
	}
	else {
		if (currentStep >= loopSize) 
			currentStep = 0;

		renderRect.x = -currentStep;

		SDL_RenderCopy(renderer, sprite, NULL, &renderRect);
	}
	if(animate)currentStep += stepSize;
}