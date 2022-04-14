#include "Obstacle.h"

Obstacle::Obstacle(SDL_Texture* tex,SDL_Rect imageDim,int width,int height,int X,int Y,int Space){

	Hitboxo1.x = X;
	Hitboxo1.y = 0;
	Hitboxo1.w = width;
	Hitboxo1.h = Y;

	float ratio = ((float)imageDim.h/(float)height);

	srcRect1 = imageDim;
	srcRect1.h = ratio*Y;

	Hitboxo2.x = X;
	Hitboxo2.y = Y + Space;
	Hitboxo2.w = width;
	Hitboxo2.h = height-Hitboxo2.y;

	srcRect2 = imageDim;
	srcRect2.h = ratio * Hitboxo2.h;

	this->tex = tex;
}
void Obstacle::Move(int speed) {
	Hitboxo1.x -= speed;
	Hitboxo2.x -= speed;
}
void Obstacle::Render(SDL_Renderer* renderer, bool showGrid) {
	SDL_RenderCopyEx(renderer, tex, &srcRect1, &Hitboxo1, NULL, NULL, SDL_FLIP_VERTICAL);
	SDL_RenderCopy(renderer, tex, &srcRect2, &Hitboxo2);
	if (showGrid) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderDrawRect(renderer, &Hitboxo1);
		SDL_RenderDrawRect(renderer, &Hitboxo2);
	}
}
bool Obstacle::OutofFrame() {
	return Hitboxo1.x+Hitboxo1.w <= 0;
}
bool Obstacle::InFrame(int width) {
	return Hitboxo1.x < width;
}