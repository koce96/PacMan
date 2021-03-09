#include "GameObject.h"
#include "Game.h"


GameObject::GameObject(const char* texturessheet, int x, int y)
{
	objTexture = Game::loadTexture(texturessheet);
	xpos = x;
	ypos = y;
}

GameObject::~GameObject()
{
}

void GameObject::update() {

	xpos++;
	ypos++;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}

void GameObject::render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
} 