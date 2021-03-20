#pragma once
#include "Collider.h"
#include "Components.h"

class Player : public Component {
private:
	Entity *ent;

public:
	bool dead = false;
	int count = 0;

	void init() {
		ent = entity;
	}

	void enemyCol(Entity& entB) {
		if (Collision::ATE(ent->getComponent<Collider>().collider , entB.getComponent<Collider>().collider, 10)) {
			if (entB.getComponent<Enemy>().scared == 1) {
				entB.getComponent<Enemy>().dead = true;
			}
			else
			{
				if (count == 0) {
					ent->getComponent<SpriteC>().setTex("Assets/lose.png", 11);
					dead = true;
				}
				count++;
				if (count == 20) {
					ent->getComponent<SpriteC>().setTex("Assets/space.png", 1);
				}
			}
		}
	}
};