#include "Background.h"

int _windowWidth;
int _windowHeight;

Background::Background(){}

Background::Background(SDL_Renderer* renderer, TextureLoader tl,int windowWidth, int windowHeight) {
	_windowWidth = windowWidth;
	_windowHeight = windowHeight;

	bgLoop = tl.LoadTexture(renderer, "sprites\\backgroundLoop.png");
	//mountains
	int bgLoopTexWidth, bgLoopTexHeight;
	SDL_QueryTexture(bgLoop, NULL, NULL, &bgLoopTexWidth, &bgLoopTexHeight);

	float loopWidthRatio = 3*(float)windowWidth / (float)bgLoopTexWidth;

	loopPlane = { 0,150,windowWidth,(int)(bgLoopTexHeight * loopWidthRatio) };

	backgroundSprite = SpriteHandler(bgLoop, 0, loopPlane, loopWidthRatio* (bgLoopTexWidth/3), 800);
	//trees
	treesLoop = tl.LoadTexture(renderer, "sprites\\trees.png");
	SDL_QueryTexture(treesLoop, NULL, NULL, &bgLoopTexWidth, &bgLoopTexHeight);

	loopWidthRatio = 2 * (float)windowWidth / (float)bgLoopTexWidth;

	treePlane = { 0,250,windowWidth,(int)(bgLoopTexHeight * loopWidthRatio) };
	treesSprite = SpriteHandler(treesLoop, 0, treePlane, loopWidthRatio * (bgLoopTexWidth / 2), 300);
	//trees bg
	treesbgLoop = tl.LoadTexture(renderer, "sprites\\tree_bg.png");
	SDL_QueryTexture(treesbgLoop, NULL, NULL, &bgLoopTexWidth, &bgLoopTexHeight);

	loopWidthRatio = 2 * (float)windowWidth / (float)bgLoopTexWidth;

	treebgPlane = { 0,250,windowWidth,(int)(bgLoopTexHeight * loopWidthRatio) };
	treesbgSprite = SpriteHandler(treesbgLoop, 0, treebgPlane, loopWidthRatio * (bgLoopTexWidth / 2), 450);
	//clouds
	cloudLoop = tl.LoadTexture(renderer, "sprites\\clouds.png");
	SDL_QueryTexture(cloudLoop, NULL, NULL, &bgLoopTexWidth, &bgLoopTexHeight);
	SDL_SetTextureBlendMode(cloudLoop, SDL_BLENDMODE_ADD);
	SDL_SetTextureAlphaMod(cloudLoop, 70);
	loopWidthRatio = 2*(float)windowWidth / (float)bgLoopTexWidth;

	cloudPlane = { 0,50,windowWidth,(int)(bgLoopTexHeight * loopWidthRatio) };
	cloudSprite = SpriteHandler(cloudLoop, 0, cloudPlane, loopWidthRatio * (bgLoopTexWidth/2), 450);
	//moon
	moon = tl.LoadTexture(renderer, "sprites\\moon.png");
	int moonw, moonh;
	SDL_QueryTexture(moon, NULL, NULL, &moonw, &moonh);
	moonPlane = { windowWidth / 2 - moonw / 2,50,moonw/2,moonh/2 };
	//stars
	starsLoop = tl.LoadTexture(renderer, "sprites\\stars.png");
	SDL_QueryTexture(starsLoop, NULL, NULL, &bgLoopTexWidth, &bgLoopTexHeight);

	loopWidthRatio = 2 * (float)windowWidth / (float)bgLoopTexWidth;

	starsPlane = { 0,0,windowWidth,(int)(bgLoopTexHeight * loopWidthRatio) };
	starsSprite = SpriteHandler(starsLoop, 0, starsPlane, loopWidthRatio * (bgLoopTexWidth / 2), 1000);
	
	//mooneffect
	moonEffect = tl.LoadTexture(renderer, "sprites\\bgeffect.png");
	int mew, meh;
	SDL_QueryTexture(moonEffect,NULL,NULL,&mew,&meh);
	effectPlane = {0,0,windowWidth,meh };
	SDL_SetTextureBlendMode(moonEffect, SDL_BLENDMODE_ADD);
}

void Background::Render(SDL_Renderer* renderer,bool animate) {
	starsSprite.Render(renderer, starsPlane, 0, animate);
	SDL_RenderCopy(renderer, moon, NULL, &moonPlane);
	SDL_RenderCopy(renderer, moonEffect, NULL, &effectPlane);
	backgroundSprite.Render(renderer, loopPlane,0,animate);
	treesbgSprite.Render(renderer, treebgPlane, 0, animate);
	treesSprite.Render(renderer, treePlane,0,animate);
	cloudSprite.Render(renderer, cloudPlane, 0, animate);
}