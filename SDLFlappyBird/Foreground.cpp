#include "Foreground.h"

Foreground::Foreground() {}

Foreground::Foreground(int numberOfSnowflakes, int windowWidth, int windowHeight,TextureLoader& tl, SDL_Renderer* renderer) {
	//snowflake
	_windowWidth = windowWidth;
	_windowHeight = windowHeight;
	numberOfFlakes = numberOfSnowflakes;
	snowflake = tl.LoadTexture(renderer, "sprites\\snowflake.png");
	AddSnowflakes();
}
void Foreground::Render(SDL_Renderer* renderer,int moveSpeed) {
	RenderSnowflakes(renderer, moveSpeed);
}
void Foreground::AddSnowflake() {
	int size = 10;
	int x = rand() % (_windowWidth - size) + _windowWidth;
	int y = rand() % (2 * size);
	int speed = (rand() % 3) + 1;
	Snowflake sf(snowflake, x, -y, size*speed, speed);
	snowflakes.push_back(sf);
}
void Foreground::AddSnowflakes() {
	for (int i = 0; i < numberOfFlakes; i++)
		AddSnowflake();
}
void Foreground::RenderSnowflakes(SDL_Renderer* renderer,int moveSpeed) {
	std::deque<Snowflake>::iterator it = snowflakes.begin();
	int removed = 0;
	while (it != snowflakes.end()) {
		it->Render(renderer, moveSpeed);
		if (!it->IsIn(_windowWidth, _windowHeight)) {
			it = snowflakes.erase(it);
			removed++;
		}
		else {
			it++;
		}
	}
	for (int i = 0; i < removed; i++) {
		AddSnowflake();
	}
}
