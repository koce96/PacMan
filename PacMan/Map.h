#pragma once
#include "Game.h"
#include "Entities.h"
#include "Collider.h"
#include "Collision.h"
#include "Components.h"
#include <vector>

using namespace std;


class Map
{
public:
	Map();
	~Map();

	
	void loadMap(int arr[20][25]);
	void drawMap();
	vector<Collider> whyt;

private:
	SDL_Rect src, dest;

	SDL_Texture* space;
	SDL_Texture* walls;
	SDL_Texture* gate;

	int map[20][25];
};

