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
	void change(int pos1,int pos2);
	vector<Collider> wallsV;
	vector<Collider> dotsV;
	vector<Collider> intV;

private:
	SDL_Rect src, dest;

	SDL_Texture* space;
	SDL_Texture* walls;
	SDL_Texture* gate;
	SDL_Texture* dots;
	SDL_Texture* pills;

	int map[20][25];
};

