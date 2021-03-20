#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

using namespace std;

class Game
{
public:
	Game();
	~Game();

	int points = 0;
	string point;
	int finalScreen = 0;

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	static SDL_Texture*	loadTexture(const char* fileName);
	static void	Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
	static SDL_Event event;
	static SDL_Renderer *renderer;

	void handleEvents();
	void update();
	void clear();
	void render();
	bool running()
	{
		return isRunning;
	}

private:
	bool isRunning;
	int tryi;
	SDL_Window *window;
};

