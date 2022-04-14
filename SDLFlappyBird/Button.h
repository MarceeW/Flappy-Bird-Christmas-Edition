#pragma once
#include "SDL.h"

class Button
{
public:
	Button();
	Button(SDL_Rect rect, SDL_Texture* image, SDL_Texture* imageOn);
	SDL_Texture* ButtonImage;
	SDL_Texture* ButtonImageOn;
	SDL_Rect location;

	void Render(SDL_Renderer* renderer);
	bool IsIn(SDL_Point& mousePos);
private:
	bool isActive;
};

