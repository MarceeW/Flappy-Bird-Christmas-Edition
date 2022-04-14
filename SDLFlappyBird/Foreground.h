#pragma once

#include "SDL.h"
#include "Snowflake.h"
#include "TextureLoader.h"

#include <deque>

class Foreground
{
public:
	Foreground();
	Foreground(int numberOfSnowflakes, int windowWidth, int windowHeight,TextureLoader& tl, SDL_Renderer* renderer);

	void Render(SDL_Renderer* renderer,int moveSpeed);
private:
	void AddSnowflakes();
	void AddSnowflake();
	void RenderSnowflakes(SDL_Renderer* renderer,int moveSpeed);

	int _windowWidth=0, _windowHeight = 0;

	int numberOfFlakes=0;
	SDL_Texture* snowflake = nullptr;
	std::deque<Snowflake> snowflakes;
};

