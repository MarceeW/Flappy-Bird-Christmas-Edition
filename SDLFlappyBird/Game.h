#pragma once
#include "SDL.h"
#include "Bird.h"
#include "Obstacle.h"
#include "Ground.h"
#include "Button.h"
#include "TextureLoader.h"
#include "TextManager.h"
#include "Background.h"
#include "Foreground.h"

#include <deque>
#include <ctime>
#include <cstdlib>
#include <string>

class Game
{
public:
	Game(int width,double ratio);
	~Game();

	void Run();

private:
	void Reset();
	void Render();
	void Input();
	void Update();
	void DeadScene();
	void AddObstacles();
	void AddObstacle();
	void RenderScoreText();

	bool isRunning;
	int windowWidth;
	int windowHeight;
	int score;

	Bird bird;
	Ground ground;
	Background bg;
	Foreground fg;
	Button test;
	TextManager scoreText;
	TextureLoader tl;
	std::deque<Obstacle> obstacles;

	SDL_Window* window;
	SDL_Renderer* renderer;
};