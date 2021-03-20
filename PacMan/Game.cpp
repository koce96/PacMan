#include "Game.h"
#include "Map.h"
#include "Components.h"
#include "Collision.h"
#include <ctime>
#include "Text.h"
#include "Enemy.h"
#include "Player.h"

SDL_Event Game::event;
Map* map;
SDL_Renderer* Game::renderer = nullptr;
Manager manager;

auto& pacman(manager.addEntity());
auto& red(manager.addEntity());
auto& green(manager.addEntity());
auto& blue(manager.addEntity());
auto& orange(manager.addEntity());

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
	} 

	if (TTF_Init() == -1) {
			cout << "Failed to init ttf!" << endl;
	}

	map = new Map();

	pacman.addComponent<PositionC>(384,384,32,32,1);
	pacman.addComponent<SpriteC>("Assets/pacman.png",3,140);
	pacman.addComponent<Controls>();
	pacman.addComponent<Collider>("pacman");
	pacman.addComponent<Player>();

	red.addComponent<PositionC>(384, 224, 32, 32, 1);
	red.addComponent<SpriteC>("Assets/red.png", 8, 400);
	red.addComponent<Collider>("red");
	red.addComponent<Enemy>();

	blue.addComponent<PositionC>(352, 320, 32, 32, 1);
	blue.addComponent<SpriteC>("Assets/blue.png", 8, 400);
	blue.addComponent<Collider>("blue");
	blue.addComponent<Enemy>();
	blue.getComponent<Enemy>().setVel(0, 0);

	orange.addComponent<PositionC>(416, 320, 32, 32, 1);
	orange.addComponent<SpriteC>("Assets/orange.png", 8, 400);
	orange.addComponent<Collider>("orange");
	orange.addComponent<Enemy>();
	orange.getComponent<Enemy>().setVel(0, 0);

	green.addComponent<PositionC>(384, 320, 32, 32, 1);
	green.addComponent<SpriteC>("Assets/green.png", 8, 400);
	green.addComponent<Collider>("green");
	green.addComponent<Enemy>();
	green.getComponent<Enemy>().setVel(0, 0);

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
	pacman.getComponent<PositionC>().saveXY();
	red.getComponent<PositionC>().saveXY();
	blue.getComponent<PositionC>().saveXY();
	green.getComponent<PositionC>().saveXY();
	orange.getComponent<PositionC>().saveXY();
	manager.refresh();
	manager.update();

	pacman.getComponent<Player>().enemyCol(red);
	pacman.getComponent<Player>().enemyCol(blue);
	pacman.getComponent<Player>().enemyCol(orange);
	pacman.getComponent<Player>().enemyCol(green);

	for (size_t a = 0; a < map->dotsV.size(); a++) {
		if (Collision::ATE(pacman.getComponent<Collider>().collider,
			map->dotsV[a].collider,20) && map->dotsV[a].tag == "dots" || Collision::ATE(pacman.getComponent<Collider>().collider,
				map->dotsV[a].collider, 20) && map->dotsV[a].tag == "pills") {
			if (map->dotsV[a].tag == "pills") {
				if (red.getComponent<Enemy>().wandering == false) {
					red.getComponent<Enemy>().scared = true;
				}
				if (blue.getComponent<Enemy>().wandering == false) {
					blue.getComponent<Enemy>().scared = true;
				}
				if (orange.getComponent<Enemy>().wandering == false) {
					orange.getComponent<Enemy>().scared = true;
				}
				if (green.getComponent<Enemy>().wandering == false) {
					green.getComponent<Enemy>().scared = true;
				}
			}
			map->dotsV[a].tag = "space";
			map->change(map->dotsV[a].collider.x /32, map->dotsV[a].collider.y /32);
			map->dotsV[a].newText(map->dotsV[a].collider.y, map->dotsV[a].collider.x);
			points += 10;
			point = to_string(points);
		}
	}
	if (points >= 500) {
		green.getComponent<Enemy>().engage();
		green.getComponent<Enemy>().wandering = false;
	}
	if (points >= 1500) { 
		blue.getComponent<Enemy>().engage(); 
	blue.getComponent<Enemy>().wandering = false;
	}
	if (points >= 1900) { 
		orange.getComponent<Enemy>().engage();
		orange.getComponent<Enemy>().wandering = false;
	}
	red.getComponent<Enemy>().engage();
	green.getComponent<Enemy>().wander(288,320);
	blue.getComponent<Enemy>().wander(288, 320);
	orange.getComponent<Enemy>().wander(288, 320);
	red.getComponent<Enemy>().wander(288, 320);

		for (size_t x = 0; x < map->intV.size(); x++) {
			red.getComponent<Enemy>().move(map->intV[x], pacman);
			orange.getComponent<Enemy>().move(map->intV[x], pacman);
			green.getComponent<Enemy>().randomMove(map->intV[x]);
			if (points < 2000) {
				blue.getComponent<Enemy>().randomMove(map->intV[x]);
			}
			else blue.getComponent<Enemy>().move(map->intV[x], pacman);
			if (points < 2200) {
				orange.getComponent<Enemy>().randomMove(map->intV[x]);
			}
			else orange.getComponent<Enemy>().move(map->intV[x], pacman);
		}
		for (size_t x = 0; x < map->wallsV.size(); x++) {
			if (Collision::AABB(pacman.getComponent<Collider>().collider,
				map->wallsV[x].collider)) {
				pacman.getComponent<PositionC>().collided();
			}
			red.getComponent<Enemy>().collide(map->wallsV[x], pacman);
			green.getComponent<Enemy>().collide(map->wallsV[x], pacman);
			orange.getComponent<Enemy>().collide(map->wallsV[x], pacman);
			blue.getComponent<Enemy>().collide(map->wallsV[x], pacman);
		}

		red.getComponent<Enemy>().respawn();
		green.getComponent<Enemy>().respawn();
		orange.getComponent<Enemy>().respawn();
		blue.getComponent<Enemy>().respawn();

		if (pacman.getComponent<Player>().dead || points == 2360) {
			red.getComponent<Enemy>().setVel(0,0);
			green.getComponent<Enemy>().setVel(0, 0);
			orange.getComponent<Enemy>().setVel(0, 0);
			blue.getComponent<Enemy>().setVel(0, 0);
			pacman.getComponent<PositionC>().velocity = 0;
			finalScreen++;
			if (finalScreen == 250) {
				isRunning = false;
			}
		}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->drawMap();
	manager.draw();
	Text showPoints("Assets/Emmett__.ttf", 20, "Points:" + point, { 255,255,255,255 });
	showPoints.display(1, 0);
	if (pacman.getComponent<Player>().dead) {
		Text lose("Assets/babyk___.ttf", 100, "You Lose!" , { 255,0,0,255 });
		lose.display(180, 200);
	}
	if (points == 2360) {
		Text win("Assets/babyk___.ttf", 100, "You Win!", { 255,0,0,255 });
		win.display(180, 200);
	}
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