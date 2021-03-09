#pragma once
#include "SDL.h"
#include "Components.h"
#include "Game.h"

class SpriteC : public Component {
private:
	PositionC *position;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:
	SpriteC() = default;
	SpriteC(const char* path) {
		setTex(path);
	}

	SpriteC(const char* path, int nFrames, int nSpeed) {
		animated = true;
		frames = nFrames;
		speed = nSpeed;
		setTex(path);
	}

	~SpriteC() {
		SDL_DestroyTexture(texture);
	}
	
	void setTex(const char* path) {
		texture = Game::loadTexture(path);
	}

	void init() override {
		position = &entity->getComponent<PositionC>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = position->width;
		srcRect.h = position->height;
		//destRect.w = destRect.h = 64;

	}
	void update() override {
		if (animated) {
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);


		}

		destRect.x = position->x();
		destRect.y = position->y();
		destRect.w = position->width * position->scale;
		destRect.h = position->height * position->scale;
	}
	void draw() override {
		Game::Draw(texture, srcRect, destRect);
	}
};
