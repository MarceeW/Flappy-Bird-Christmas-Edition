#pragma once
#include "SDL.h"

class Obstacle
{
public:
	SDL_Rect Hitboxo1{ 0,0,0,0 };
	SDL_Rect Hitboxo2{ 0,0,0,0 };

	Obstacle(SDL_Texture* tex, SDL_Rect imageDim,int width,int height,int X,int Y,int Space);

	void Render(SDL_Renderer* renderer, bool showGrid);
	void Move(int speed);
	bool OutofFrame();
	bool InFrame(int width);
	bool passed = false;
private:
	SDL_Texture* tex= nullptr;
	SDL_Rect srcRect1{0,0,0,0};
	SDL_Rect srcRect2{ 0,0,0,0 };
};