#define SDL_MAIN_HANDLED	//Fixing error

#include "Game.h"

Game *game = nullptr;

int main(int argc, const char * argv[]) {
	SDL_SetMainReady();		//Fixing error

	const int fps = 60;
	const int frameDelay = 1000 / fps;
	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->init("PACMAN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	while (game->running()) {

		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay > frameTime);
		}
	}

	game->clear();

	return 0;
}