#pragma once
#include "SDL.h"
class Collision
{
public:
	Collision();
	~Collision();
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
};

