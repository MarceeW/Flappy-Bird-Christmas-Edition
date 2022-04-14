#include "Button.h"

Button::Button(){}
Button::Button(SDL_Rect rect,SDL_Texture* image, SDL_Texture* imageOn) {
	location = rect;
	ButtonImage = image;
	ButtonImageOn = imageOn;
	isActive = false;
}
void Button::Render(SDL_Renderer* renderer) {
	if (isActive) {
		SDL_SetRenderDrawColor(renderer, 0, 100, 30, 255);
	}
	else
		SDL_SetRenderDrawColor(renderer, 0, 30, 100, 255);

	SDL_RenderFillRect(renderer, &location);
}
bool Button::IsIn(SDL_Point &mousePos) {
	isActive= mousePos.y >= location.y && mousePos.y <= location.y + location.h &&
		mousePos.x >= location.x && mousePos.x <= location.x + location.w;
	return isActive;
}

