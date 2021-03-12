#include "Collision.h"
#include "Collider.h"


bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB) {
	if (
		recA.x + recA.w  - 5  >= recB.x &&
		recB.x + recB.w - 5 >= recA.x &&
		recA.y + recA.h - 5 >= recB.y &&
		recB.y + recB.h - 5 >= recA.y
		)
	{
		std::cout << recA.x << recA.y << " hit: " << recB.x << recB.y << std::endl; return true;}

	if (
		recA.x <= 30 || recA.x + recA.w >= 770
		) {return true;}
	if (
		recA.y <= 30 || recA.y + recA.h >= 610
		) {return true;}
	
	return false;
}

bool Collision::AABB(const Collider& colA, const Collider& colB)
{
	if (AABB(colA.collider, colB.collider))
	{
		//std::cout << colA.tag << " hit: " << colB.tag << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}