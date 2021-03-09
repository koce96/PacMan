#pragma once
#include "Components.h"
#include "Entities.h"
#include "Game.h"

class Controls : public Component {
public:
	PositionC *position;

	void init() {
		position = &entity->getComponent<PositionC>();
	}

	void update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_UP:
				position->direction = 1;
				break;
			case SDLK_DOWN:
				position->direction = 2;
				break;
			case SDLK_LEFT:
				position->direction = 3;
				break;
			case SDLK_RIGHT:
				position->direction = 4;
				break;
			default:
				break;
			}

		}
	}
};
