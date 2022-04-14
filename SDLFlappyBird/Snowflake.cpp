#include "Snowflake.h"

Snowflake::Snowflake(){}

Snowflake::Snowflake(SDL_Texture* tex,int x,int y,int size,int yspeed) {
	this->tex = tex;
	this->yspeed = yspeed;
	pos = { x,y,size,size };
}
void Snowflake::Render(SDL_Renderer* renderer,int xspeed) {
	SDL_RenderCopy(renderer, tex, NULL, &pos);
	pos.x -= pos.w/xspeed;
	pos.y += yspeed;
}
bool Snowflake::IsIn(int width, int height) {
	return pos.x > -pos.w && pos.y + pos.h < height;
}
