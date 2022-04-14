// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Game.h"

int main(int argc, char* argv[]) {
	Game* game=new Game(720,3.0/4.0);
	game->Run();
	delete game;
	return 0;
}