#include "Collision.h"
#include "Collider.h"


bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB) {
	if (
		recA.x + recA.w  - 5  >= recB.x &&
		recB.x + recB.w - 5 >= recA.x &&
		recA.y + recA.h - 5 >= recB.y &&
		recB.y + recB.h - 5 >= recA.y
		)
	{return true;}

	if (
		recA.x <= 30 || recA.x + recA.w >= 770
		) {return true;}
	if (
		recA.y <= 30 || recA.y + recA.h >= 610
		) {return true;}
	
	return false;
}


bool Collision::ATE(const SDL_Rect& recA, const SDL_Rect& recB, int proximity) {
	if (
		recA.x + recA.w - proximity >= recB.x &&
		recB.x + recB.w - proximity >= recA.x &&
		recA.y + recA.h - proximity >= recB.y &&
		recB.y + recB.h - proximity >= recA.y
		)
	{
		return true;
	}
	return false;
}