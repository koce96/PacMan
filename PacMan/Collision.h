#pragma once
#include "SDL.h"

class Collider;

class Collision
{
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool ATE(const SDL_Rect& recA, const SDL_Rect& recB, int proximity);
};

