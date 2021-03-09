#include "Collision.h"


Collision::Collision()
{
}


Collision::~Collision()
{
}

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB) {
	if (
		recA.x + recA.w + 1 >= recB.x &&
		recB.x + recB.w + 1 >= recA.x &&
		recA.y + recA.h + 1 >= recB.y &&
		recB.y + recB.h + 1 >= recA.y
		)
	{return true;}

	if (
		recA.x <= 0 || recA.x + recA.w >= 800
		) {return true;}
	if (
		recA.y <= 0 || recA.y + recA.h >= 610
		) {return true;}
	
	return false;
}