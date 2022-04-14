#include "Bird.h"

int modelVsHitbox = 0;
int effectSize = 300;

Bird::Bird() {}

Bird::Bird(SDL_Renderer* renderer,TextureLoader tl,int WindowWidth,int WindowHeight,int size,int jumpSize) {
	
	Hitbox.x = WindowWidth / 2 - size/2;
	Hitbox.y = WindowHeight / 2 - size/2;
	Hitbox.w = size;
	Hitbox.h = size;

	modelBox = Hitbox;
	modelBox.y -= modelVsHitbox;
	modelBox.w = size+modelVsHitbox * 2;
	modelBox.h = size+modelVsHitbox * 2;

	steps = M_PI / (jumpSize/4);
	this->jumpSize = jumpSize;

	fallSpeed = defaultFallSpeed;
	startY = Hitbox.y;

	SDL_Texture* tex = tl.LoadTexture(renderer, "sprites\\birds.png");
	int height, width = 17;
	birdSprite = SpriteHandler(tex, 1, modelBox, width, 8);
	SDL_QueryTexture(tex, NULL, NULL, NULL, &height);

	modelBox.w *= (float)width / (float)height;
	modelBox.x = Hitbox.x - ((float)modelBox.w / (float)modelBox.h + 1) * modelVsHitbox;

	SDL_Texture* tex2 = tl.LoadTexture(renderer, "sprites\\particle.png");
	particlePos = Hitbox;;
	birdParticle = SpriteHandler(tex2, 1, particlePos, 0, 3);
	//effect
	effectBox = { Hitbox.x-effectSize,Hitbox.y - effectSize,
		effectSize*2+ modelBox.w,effectSize*2+ modelBox.h };
	effect = tl.LoadTexture(renderer, "sprites\\birdEffect.png");
	SDL_SetTextureBlendMode(effect, SDL_BLENDMODE_ADD);
}
void Bird::Render(SDL_Renderer* renderer, int obstacleSpeed,bool showGrid) {
	if (!birdParticle.Finished())birdParticle.Render(renderer, particlePos, 0, true);
	particlePos.x -= obstacleSpeed;
	birdSprite.Render(renderer, modelBox, animationAngel, true);
	SDL_RenderCopy(renderer, effect, NULL, &effectBox);
	if (showGrid) {
		if (isDead)
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		else
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderDrawRect(renderer, &Hitbox);
	}
}
void Bird::Reset(int WindowWidth, int WindowHeight) {
	Hitbox.x = WindowWidth / 2 - Hitbox.w / 2;
	Hitbox.y = WindowHeight / 2 - Hitbox.h / 2;

	modelBox.y = Hitbox.y - modelVsHitbox;
	modelBox.x = Hitbox.x - ((float)modelBox.w / (float)modelBox.h + 1) * modelVsHitbox;

	effectBox = { Hitbox.x - effectSize,Hitbox.y - effectSize,
		effectSize * 2 + modelBox.w,effectSize * 2 + modelBox.h };

	isDead = false;
	isFalling = true;
	isGrounded = false;
	autoFly = false;

	currentStep = 0;
	fallSpeed = defaultFallSpeed;
	startY = Hitbox.y;
	birdSprite.Reset();
	animationAngel = 360.0;
	Jump();
}
void Bird::AutoFly() {
	int lastPos = Hitbox.y;
	Hitbox.y = startY - sin(currentStep += (float)steps) * jumpSize / 2;
	modelBox.y = Hitbox.y - modelVsHitbox;
	effectBox.y = modelBox.y - effectSize;
	Rotate(lastPos);
}
void Bird::Fly(SDL_Rect& ground) {
	int lastPos = Hitbox.y;
	if (!autoFly) {
		if (currentStep >= M_PI) {
			isFalling = true;
			currentStep = 0;
		}
		if (!isFalling) {
			Hitbox.y = startY - sin(currentStep += (float)steps) * jumpSize;
		}
		else if (!GroundCollision(ground)) {
			double powSpeed = pow(fallSpeed, 2.0);
			if (Hitbox.y + Hitbox.h > ground.y)
				powSpeed = (float)(ground.y - (Hitbox.y + Hitbox.h));
			Hitbox.y += powSpeed;
			fallSpeed += 0.1;
		}
		else {
			isDead = true;
			isGrounded = true;
		}
		modelBox.y = Hitbox.y - modelVsHitbox;
		effectBox.y = modelBox.y - effectSize;
	}
	else
		AutoFly();
	Rotate(lastPos);
}
void Bird::Rotate(int lastPos) {
	float rotationSpeed = 3;
	if (autoFly)rotationSpeed = 1;
	if (lastPos < Hitbox.y && animationAngel < 360 + 90) {
		animationAngel += rotationSpeed;
	}
}
bool Bird::GroundCollision(SDL_Rect& ground) {
	return ground.y == Hitbox.y + Hitbox.h;
}
void Bird::Jump() {
	if (!isDead && !autoFly && Hitbox.y >= 0) {
		fallSpeed = defaultFallSpeed;
		isFalling = false;
		currentStep = 0;
		startY = Hitbox.y;
		birdSprite.Reset();
		animationAngel = 360-30;
		particlePos = Hitbox;

		birdParticle.Reset();
	}
}
void Bird::IsCollided(SDL_Rect& rect) {
	if (!isDead) {
		isDead = ((Hitbox.x + Hitbox.w >= rect.x && Hitbox.x <= rect.x + rect.w)
			&& (Hitbox.y + Hitbox.h >= rect.y && Hitbox.y <= rect.y + rect.h));
	}
	if (isDead) {
		if (rect.x < Hitbox.x+Hitbox.w && Hitbox.x+Hitbox.w-rect.x<Hitbox.w/3 && 
			rect.x>Hitbox.x && Hitbox.y<rect.y + rect.h && Hitbox.y + Hitbox.h>rect.y)
			Hitbox.x = rect.x - Hitbox.w;
		else if (rect.y > 0 && rect.y<Hitbox.y+Hitbox.h && Hitbox.x + Hitbox.w > rect.x){
			Hitbox.y = rect.y - Hitbox.h;
			isGrounded = true;
		}
		modelBox.x = Hitbox.x - ((float)modelBox.w / (float)modelBox.h + 1) * modelVsHitbox;
		modelBox.y = Hitbox.y - modelVsHitbox;
		effectBox.y = modelBox.y - effectSize;
	}
}