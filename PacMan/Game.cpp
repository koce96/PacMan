#include "Game.h"
#include "Map.h"
#include "Components.h"
#include "Collision.h"
//#include "Entities.h"
//#include "GameObject.h"

SDL_Event Game::event;
Map* map;
SDL_Renderer* Game::renderer = nullptr;
Manager manager;

//GameObject* player;

auto& player(manager.addEntity());
auto& red(manager.addEntity());
auto& wall(manager.addEntity());

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		cout << "Subsystem Init!...." << endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			cout << "Window Created!" << endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			cout << "Renderer Created!" << endl;
		}

		isRunning = true;
	} //else {
	//isRunning = false;
	//}

	

	//SDL_Surface* tempSurface = IMG_Load("Assets/pacman.png");
	//playerTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	//SDL_FreeSurface(tempSurface);
	//player = new GameObject("Assets/gate.png", 0, 0);
		map = new Map();

	//newPlayer.addComponent<PositionComponent>();	
	//newPlayer.getComponent<PositionComponent>().setPos(500, 500);
	player.addComponent<PositionC>(384,320,32,32,2);
	player.addComponent<SpriteC>("Assets/sprite1.png",3,150);
	player.addComponent<Controls>();
	player.addComponent<Collider>("player");

	red.addComponent<PositionC>(300, 400, 32, 32, 2);
	red.addComponent<SpriteC>("Assets/red.png", 2, 200);
	red.addComponent<Collider>("red");

	/*wall.addComponent<PositionC>(0, 0, 32, 800, 1);
	wall.addComponent<SpriteC>("Assets/gate.png");
	wall.addComponent<Collider>("wall");
*/
	wall.addComponent<PositionC>(96, 96, 32, 32, 1);
	wall.addComponent<PositionC>(128, 128, 32, 32, 1);
	wall.addComponent<SpriteC>("Assets/gate.png");
	wall.addComponent<Collider>("wall");
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update() 
{	
	//player->update();
	player.getComponent<PositionC>().saveXY();
	manager.refresh();
	manager.update();
	//cout << newPlayer.getComponent<PositionComponent>().x() << "," << newPlayer.getComponent<PositionComponent>().y() << endl;

	//if (player.getComponent<PositionC>().x() > 100) {
	//	player.getComponent<SpriteC>().setTex("Assets/logo.png");
	//}
	
	if (Collision::AABB(player.getComponent<Collider>().collider,
		wall.getComponent<Collider>().collider)) {
		cout << "Hit!!" << endl;
		player.getComponent<PositionC>().collided();
		//player.getComponent<PositionC>().velocity * -1;
	}
	cout << player.getComponent<PositionC>().velocity << endl;
	if (Collision::AABB(player.getComponent<Collider>().collider,
		red.getComponent<Collider>().collider)) {
		cout << "Hit!!" << endl;
		red.getComponent<SpriteC>().setTex("Assets/ghost.png");
		//player.getComponent<PositionC>().velocity * -1;
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->drawMap();
	manager.draw();
	//player->render();
	SDL_RenderPresent(renderer);
}

void Game::clear()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "GAME QUIT!" << endl;
}

SDL_Texture* Game::loadTexture(const char* fileName) {
	SDL_Surface* tempSurface = IMG_Load(fileName);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	
	return tex; 
}

void Game::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}