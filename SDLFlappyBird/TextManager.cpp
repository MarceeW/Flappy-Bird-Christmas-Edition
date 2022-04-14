#include "TextManager.h"

TextManager::TextManager() {}

TextManager::TextManager(const char* fontLocation,int size,int shadowFlag) {
	if (TTF_Init() < 0)
		SDL_Log("Error, can't init TTF file");
	font = TTF_OpenFont(fontLocation, size);
	renderedText = nullptr;
	renderedTextShadow = nullptr;
	shadow = shadowFlag;
}
SDL_Texture* TextManager::RenderTextTexture(SDL_Renderer* renderer, const char* text,SDL_Color& fg) {
	SDL_Surface* surf = TTF_RenderText_Solid(font, text, fg);
	SDL_DestroyTexture(renderedText);
	renderedText = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	SDL_QueryTexture(renderedText, NULL, NULL, &position.w, &position.h);
	if (shadow) {
		SDL_Surface* shadowSurf = TTF_RenderText_Solid(font, text, SDL_Color{ 0,0,0 });
		SDL_DestroyTexture(renderedTextShadow);
		renderedTextShadow = SDL_CreateTextureFromSurface(renderer, shadowSurf);
		SDL_FreeSurface(shadowSurf); 
		shadowPosition.w = position.w;
		shadowPosition.h = position.h;
	}
	return renderedText;
}
SDL_Point TextManager::GetSize() {
	return{ position.w,position.h };
}
void TextManager::Render(SDL_Renderer* renderer) {
	if(shadow)SDL_RenderCopy(renderer, renderedTextShadow, NULL, &shadowPosition);
	SDL_RenderCopy(renderer, renderedText, NULL, &position);
}
void TextManager::SetPosition(SDL_Point& pos) {
	position.x = pos.x;
	position.y = pos.y;
	if (shadow) {
		shadowPosition.x = pos.x - 5;
		shadowPosition.y = pos.y + 5;
	}
}