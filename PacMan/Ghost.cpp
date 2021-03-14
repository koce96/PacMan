#include "Ghost.h"
#include "Game.h"



Ghost::Ghost()
{
}


Ghost::~Ghost()
{
}

 void Ghost::moveGhost(double posAx, double posAy, double posBx, double posBy) {
	if (posAx > posBx) {
		posBx++;
		//return true;
	}
	if (posAx < posBx) {
		posBx--;
		//return true;
	}
	if (posAy > posBy) {
		posBy++;
		//return true;
	}
	if (posAy < posBy) {
		posBy--;
		//return true;
	}
	//return false;
	
 }