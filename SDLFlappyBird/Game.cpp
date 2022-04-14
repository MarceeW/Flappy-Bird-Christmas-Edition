#include "Game.h"

int tubeWidth = 150;
int obstacleSpeed = 5;
SDL_Texture* tubeTexture = nullptr;
SDL_Texture* tubeTextureRotated = nullptr;
SDL_Texture* nightEffect = nullptr;
SDL_Rect tubeTextureSize{0,0,0,0};
bool showGrid = false;

Game::Game(int height,double ratio){
	if (SDL_Init(SDL_INIT_VIDEO))
		SDL_Log("Error occured during loading libraries!");
	window = SDL_CreateWindow(
		"Flappy Bird",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		height * ratio,
		height,
		SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	bird = Bird(renderer,tl,windowWidth, (int)(windowWidth), windowHeight / 13, 100);
	ground = Ground(renderer,tl,windowHeight, windowWidth);

	tubeTexture = tl.LoadTexture(renderer, "sprites\\tube.png");
	tubeTextureSize.x = 0;
	tubeTextureSize.y = 0;
	SDL_QueryTexture(tubeTexture, NULL, NULL, &tubeTextureSize.w, &tubeTextureSize.h);

	srand(time(0));
	bg = Background(renderer, tl, windowWidth,windowHeight);

	isRunning = false;
	score = 0;

	AddObstacles();
	test = Button(SDL_Rect{ 200,200,50,50 }, nullptr, nullptr);

	scoreText = TextManager("font\\Gameplay.ttf", windowHeight/20,1);
	RenderScoreText();

	nightEffect = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA4444, SDL_TEXTUREACCESS_TARGET, windowHeight, windowWidth);	
	SDL_SetRenderTarget(renderer, nightEffect);
	SDL_SetRenderDrawColor(renderer, 50, 0, 200, 255);
	SDL_RenderClear(renderer);
	SDL_SetTextureBlendMode(nightEffect, SDL_BLENDMODE_ADD);
	SDL_SetTextureAlphaMod(nightEffect, 70);
	SDL_SetRenderTarget(renderer, NULL);

	fg = Foreground(16, windowWidth, windowHeight, tl, renderer);
}
void Game::Reset() {
	obstacles.clear();
	AddObstacles();
	bird.Reset(windowWidth, windowHeight);
	score = 0;
	RenderScoreText();
}
void Game::RenderScoreText() {
	SDL_Color scoreColor{ 255,255,255 };
	scoreText.RenderTextTexture(renderer, std::to_string(score).c_str(), scoreColor);
	SDL_Point pos{ windowWidth / 2 - scoreText.GetSize().x / 2,100 };
	scoreText.SetPosition(pos);
}
void Game::AddObstacles() {
	for (int i = 0; i < windowWidth / 150; i++)
	{
		AddObstacle();
	}
}
Game::~Game() {
	SDL_Log("Destructor");
}
void Game::Update() {
	if (!bird.isGrounded) {
		bird.Fly(ground.Hitbox);
		if (obstacles.front().OutofFrame()) {
			AddObstacle();
			obstacles.erase(obstacles.begin());
		}
		for (std::deque<Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); it++) {
			if (!it->passed) {
				if (!bird.isDead)bird.IsCollided(it->Hitboxo1);
				bird.IsCollided(it->Hitboxo2);
				if (!bird.isDead && it->Hitboxo1.x + it->Hitboxo1.w + bird.Hitbox.w / 2 <= windowWidth / 2) {
					it->passed = true;
					score++;
					RenderScoreText();
				}
			}
			if (!bird.isDead)
				it->Move(obstacleSpeed);
		}
	}
}
void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 10, 30, 255);
	SDL_RenderClear(renderer);
	bg.Render(renderer,!bird.isDead);
	for (Obstacle& i : obstacles) {
		if (i.InFrame(windowWidth))i.Render(renderer, showGrid);
	}
	ground.Render(renderer,!bird.isDead,showGrid);
	bird.Render(renderer, obstacleSpeed, showGrid);
	scoreText.Render(renderer);
	//test.Render(renderer);
	SDL_RenderCopy(renderer, nightEffect, NULL, NULL);
	fg.Render(renderer, obstacleSpeed);
	SDL_RenderPresent(renderer);
	if (bird.isGrounded) {
		SDL_Delay(500);
		Reset();
	}
}
void Game::AddObstacle() {
	int spaceBetweenEach = windowWidth/3 + tubeWidth;
	int gap = windowHeight / 3;

	int y=(rand() % (windowHeight-ground.Hitbox.h-gap-100)) + 50;
	int x = obstacles.empty() ? windowWidth + spaceBetweenEach : obstacles.back().Hitboxo1.x + spaceBetweenEach;
	Obstacle obs(tubeTexture, tubeTextureSize, tubeWidth, windowHeight - ground.Hitbox.h, x, y, gap);
	obstacles.push_back(obs);
}
void Game::Input() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				//SDL_Point p;
				//SDL_GetMouseState(&p.x, &p.y);
				//if (test.IsIn(p))
				//	Reset();
				//else 
					bird.Jump();
			}
			else if (event.button.button == SDL_BUTTON_RIGHT) {
				showGrid = !showGrid;
			}
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_SPACE)
				bird.Jump();
			break;
		case SDL_MOUSEMOTION:
			SDL_Point p;
			SDL_GetMouseState(&p.x, &p.y);
			test.IsIn(p);
		default:
			break;
		}
	}
}
void Game::Run() {
	isRunning = true;

	const int frameDelay = 1000 / 60;

	Uint32 frameStart;
	int frameTime;
	bird.Jump();
	while (isRunning) {
		frameStart = SDL_GetTicks();
		Input();
		Update();
		Render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}
}