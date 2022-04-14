#pragma once
#include "SDL.h"
#include "SDL_TTF.h"

class TextManager
{
public:
	TextManager();
	TextManager(const char* fontLocation,int size, int shadowFlag);
	SDL_Texture* RenderTextTexture(SDL_Renderer* renderer,const char* text, SDL_Color& fg);
	void Render(SDL_Renderer* renderer);
	void SetPosition(SDL_Point& pos);
	SDL_Point GetSize();
private:
	int shadow;

	TTF_Font* font;
	SDL_Rect position;
	SDL_Rect shadowPosition;
	SDL_Texture* renderedText;
	SDL_Texture* renderedTextShadow;
};