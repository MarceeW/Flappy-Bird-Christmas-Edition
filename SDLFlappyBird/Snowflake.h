#pragma once
#include "SDL.h"

class Snowflake
{
public:
	Snowflake();
	Snowflake(SDL_Texture* tex, int x,int y, int size,int speed);
	void Render(SDL_Renderer* renderer,int xspeed);
	bool IsIn(int widt, int height);
private:
	SDL_Texture* tex=nullptr;
	SDL_Rect pos = {0,0,0,0};
	int yspeed = 0;
};

