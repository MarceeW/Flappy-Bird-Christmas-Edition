#include "Ground.h"

Ground::Ground(){}

Ground::Ground(SDL_Renderer* renderer, TextureLoader& tl, int height, int width) {
	Hitbox.x = 0;
	Hitbox.h = height/8;
	Hitbox.w = width;
	Hitbox.y = height - Hitbox.h;
	
	texture = tl.LoadTexture(renderer,"sprites\\ground.png");
	groundSprite = SpriteHandler(texture, 0,Hitbox, 20, 4);
}
void Ground::Render(SDL_Renderer* renderer,bool animate, bool showGrid) {
	groundSprite.Render(renderer, Hitbox,0,animate);
	if (showGrid) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(renderer, &Hitbox);
	}	
}
