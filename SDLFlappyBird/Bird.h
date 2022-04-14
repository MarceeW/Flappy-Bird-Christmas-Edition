#pragma once
#include "SDL.h"
#include "SpriteHandler.h"
#include "math.h"

class Bird
{
public:
	Bird();
	Bird(SDL_Renderer* renderer,TextureLoader tl,int WindowWidth, int WindowHeight,int size,int jumpSize);

	void Fly(SDL_Rect& ground);
	void Jump();
	void Render(SDL_Renderer* renderer, int obstacleSpeed,bool showGrid);
	void IsCollided(SDL_Rect& rect);
	void Reset(int WindowWidth, int WindowHeight);
	void AutoFly();
	bool IsFalling() { return isFalling; }

	SDL_Rect Hitbox = {0,0,0,0};
	bool isDead = false;
	bool autoFly = false;
	bool isGrounded = false;

private:
	bool GroundCollision(SDL_Rect& ground);
	void Rotate(int lastPos);

	SpriteHandler birdSprite;
	SpriteHandler birdParticle;
	SDL_Texture* effect=nullptr;
	SDL_Rect particlePos{0,0,0,0};
	SDL_Rect modelBox{0,0,0,0};
	SDL_Rect effectBox{ 0,0,0,0 };
	bool isFalling = false;
	int jumpSize=0;
	float fallSpeed=0.0;
	float startY=0.0;
	float steps=0.0;
	float currentStep=0.0;
	float defaultFallSpeed = 4.0;
	float animationAngel=360.0;
};

