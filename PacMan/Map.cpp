#include "Map.h"
#include "Game.h"
#include "Collision.h"

int level[20][25] = {
{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,1,1,1,1,0,1,1,1,1,0,1,0,1,1,1,1,0,1,1,1,1,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,1,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,1,0,1 },
{ 1,0,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,1,0,0,0,0,0,0,1 },
{ 1,0,1,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,1,0,1 },
{ 1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1 },
{ 1,1,1,1,0,1,0,1,0,1,1,2,2,2,1,1,0,1,0,1,0,1,1,1,1 },
{ 1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1 },
{ 1,1,1,1,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,1,1,1,1 },
{ 1,1,1,1,0,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,0,1,1,1,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,1,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,1,0,1 },
{ 1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1 },
{ 1,1,1,0,1,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,1,0,1,1,1 },
{ 1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1 },
{ 1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
};

Map::Map()
{
	space = Game::loadTexture("Assets/space.png");
	walls = Game::loadTexture("Assets/wall.png");
	gate = Game::loadTexture("Assets/gate.png");


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
}

void Map::loadMap(int arr[20][25]) {
	for (int row = 0; row < 20; row++) {
		for (int column = 0; column < 25; column++) {
			map[row][column] = arr[row][column];
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
				Game::Draw(space, src, dest);
				break;
			case 1:
				Game::Draw(walls, src, dest);
				/*auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
				tcol.addGroup(Game::groupColliders);*/
				break;
			case 2:
				Game::Draw(gate, src, dest);
				break;
					default:
				break;
			}
		}
	}
}
