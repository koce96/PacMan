#pragma once
#include<string>
#include "SDL.h"
#include "Components.h"

using namespace std;

class Collider : public Component {
public:
	SDL_Rect collider;
	string tag;

	PositionC* position;

	Collider(string t) {
		tag = t;
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
};