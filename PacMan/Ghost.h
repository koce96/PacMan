#pragma once
#include "Entities.h"
#include "SDL.h"

class Collider; 

class Ghost : public Entity
{
public:
	Ghost();
	~Ghost();
	static void moveGhost(double posAx, double posAy, double posBx, double posBy);
};

