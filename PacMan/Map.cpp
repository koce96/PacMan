#include "Map.h"
#include "Game.h"
#include "Collision.h"
#include "Entities.h"
#include "Components.h"
#include <vector>
#include <cstdlib>

using namespace std;

extern Manager manager;

int level[20][25] = {
{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
{ 1,4,0,0,0,0,5,0,0,0,0,0,1,0,0,0,0,0,5,0,0,0,0,4,1 },
{ 1,0,1,1,1,1,0,1,1,1,1,0,1,0,1,1,1,1,0,1,1,1,1,0,1 },
{ 1,5,0,0,0,0,5,0,5,0,0,5,0,5,0,0,5,0,5,0,0,0,0,5,1 },
{ 1,0,1,1,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,1,1,0,1 },
{ 1,5,0,0,5,0,5,1,5,0,0,5,0,5,0,0,5,1,5,0,5,0,0,5,1 },
{ 1,0,1,1,0,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,0,1,1,0,1 },
{ 1,0,0,0,5,1,0,1,5,3,3,3,3,3,3,3,5,1,0,1,5,0,0,0,1 },
{ 1,1,1,1,0,1,0,1,0,1,1,2,2,2,1,1,0,1,0,1,0,1,1,0,1 },
{ 1,1,1,1,5,0,5,0,5,1,3,3,3,3,3,1,5,0,5,0,5,1,1,0,1 },
{ 1,1,1,1,0,1,0,1,0,1,3,3,3,3,3,1,0,1,0,1,0,1,1,0,1 },
{ 1,1,1,1,0,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,0,1,1,0,1 },
{ 1,0,0,5,5,0,5,0,5,0,0,0,3,0,0,0,5,0,5,0,5,5,0,0,1 },
{ 1,0,1,0,1,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,1,0,1,0,1 },
{ 1,5,0,5,1,1,5,0,5,0,0,5,0,5,0,0,5,0,5,1,1,5,0,5,1 },
{ 1,1,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,1,1,1 },
{ 1,5,0,5,0,0,5,1,5,1,1,0,1,0,1,1,5,1,5,0,0,5,0,5,1 },
{ 1,0,1,1,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,1,1,1,0,1 },
{ 1,4,0,0,0,0,5,0,5,0,0,5,0,5,0,0,5,0,5,0,0,0,0,4,1 },
{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
};

Map::Map()
{
	space = Game::loadTexture("Assets/space.png");
	walls = Game::loadTexture("Assets/wall.png");
	gate = Game::loadTexture("Assets/gate.png");
	dots = Game::loadTexture("Assets/point.png");
	pills = Game::loadTexture("Assets/pill.png");


	loadMap(level);

	src.x = src.y = 0;
	src.w = dest.w = 32;
	src.h = dest.h = 32;
	dest.x = dest.y = 0;

}

Map::~Map() {
	SDL_DestroyTexture(walls);
	SDL_DestroyTexture(gate);
	SDL_DestroyTexture(space);
	SDL_DestroyTexture(dots);
}

void Map::loadMap(int arr[20][25]) {
	for (int row = 0; row < 20; row++) {
		for (int column = 0; column < 25; column++) {
			map[row][column] = arr[row][column];
			if (map[row][column] == 1 || map[row][column] == 2) {
							auto& colW(manager.addEntity());
							colW.addComponent<Collider>("walls", column * 32, row * 32, 32);
							wallsV.push_back(colW.getComponent<Collider>());
			}
			 if (map[row][column] == 0 || map[row][column] == 4 || map[row][column] == 5) {
				auto& colD(manager.addEntity());
				if (map[row][column] == 0 || map[row][column] == 5) {
					colD.addComponent<Collider>("dots", column * 32, row * 32, 32);
				}
				if (map[row][column] == 4) {
					colD.addComponent<Collider>("pills", column * 32, row * 32, 32);
				}
				dotsV.push_back(colD.getComponent<Collider>());
			}
			 if (map[row][column] == 5 || map[row][column] == 4) {
				 auto& colI(manager.addEntity());
				 colI.addComponent<Collider>("walls", column * 32, row * 32, 32);
				 intV.push_back(colI.getComponent<Collider>());
			 }
		}
		
	}
} 

void Map::drawMap() {
	int type = 0;

	for (int row = 0; row < 20; row++) {
		for (int column = 0; column < 25; column++) {
			type = map[row][column];
			dest.x = column * 32;
			dest.y = row * 32;

			switch (type)
			{
			case 0:
				Game::Draw(dots, src, dest);
				break;
			case 1:
			Game::Draw(walls, src, dest);
				break;
			case 2:
				Game::Draw(gate, src, dest);
				break;
			case 3:
				Game::Draw(space, src, dest);
				break;
			case 4:
				Game::Draw(pills, src, dest);
				break;
			case 5:
				Game::Draw(dots, src, dest);
				break;
					default:
				break;
			}
		}
	}
}

void Map::change(int pos1,int pos2) {
	map[pos2][pos1] = 3;
}