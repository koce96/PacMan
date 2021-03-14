#pragma once
#include<string>
#include "SDL.h"
#include "Components.h"

using namespace std;

class Collider : public Component {
public:
	SDL_Rect collider, src, dest;
	string tag;
	SDL_Texture* eaten = Game::loadTexture("Assets/space.png");

	PositionC* position;

	Collider(string t) {
		tag = t;
	}

	Collider(std::string t, int xpos, int ypos, int size)
	{
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
	}

	void init() override {
		if (!entity->hasComponent<PositionC>()) {
			entity->addComponent<PositionC>();
		}
		position = &entity->getComponent<PositionC>();
	}

	void update() override {
		collider.x = position->xpos;
		collider.y = position->ypos;
		collider.w = position->width * position->scale;
		collider.h = position->height * position->scale;
	}

	void newText(int destx, int desty) {
		src.h = dest.h = 32;
		src.w = dest.w = 32;
		src.x = src.y = 0;
		dest.x = destx;
		dest.y = desty;
		SDL_RenderCopy(Game::renderer, eaten, &src, &dest);
	}
};