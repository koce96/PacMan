#pragma once
#include "Collider.h"
#include "Components.h"
#include <ctime>

class Enemy : public Component {
private:
	PositionC *position;
	SpriteC *sprite;
	Map *map;
	Entity *ent;
	clock_t time;
	const char* defaultTex;
	bool collided = false;

public:
	int velX = 1;
	int velY = 0;
	int wand = 0;
	int randomInt = 0;
	bool wandering = true;
	bool set = true;
	int timer = 0;
	int seconds = 0;
	bool dead = false;
	bool scared = false;
	bool engaged = false;
	vector<Collider> wallVec;


	void init() {
		position = &entity->getComponent<PositionC>();
		sprite = &entity->getComponent<SpriteC>();
		ent = entity;
		defaultTex = ent->getComponent<SpriteC>().getTex();
	}
	
	void update() override {
		time = clock();
		seconds = (int)time / CLOCKS_PER_SEC;

		position->xpos += velX;
		position->ypos += velY;
		if (!scared) { timer = seconds + 15; }
		if (scared && !wandering) {
			if (timer > seconds) {
				if (scared && engaged == true) { sprite->setTex("Assets/scared.png", 4); }
			}
			if(timer < seconds){
				scared = false; sprite->setTex(defaultTex, 6);
			}
		}
		if (dead) { sprite->setTex("Assets/ghost.png", 4); }
	}

	void setVel(int vX, int vY) {
		velX = vX;
		velY = vY;
	}

	void randomMove(Collider& col) {
		if (ent->getComponent<Collider>().collider.x == col.collider.x && ent->getComponent<Collider>().collider.y == col.collider.y) {
			randomInt = rand() % 8 + 1;
			if (randomInt == 1 || randomInt == 8) { setVel(-1, 0);}
			else if (randomInt == 2 || randomInt == 7) { setVel(1, 0);}
			else if (randomInt == 3 || randomInt == 6) { setVel(0, -1);}
			else if (randomInt == 4 || randomInt == 5) { setVel(0, 1);}
		}
	}

	void respawn() {
		if (dead) {
			if (position->xpos < 384 ) {
				velX = 1;
			}
			if (position->xpos > 384) {
				velX = -1;
			}
			if (position->ypos < 320){
				velY = 1;
			}
			if (position->ypos > 320) {
				velY = -1;
			}
			else if (position->xpos == 384 && position->ypos == 320 || position->xpos == 384 && position->ypos == 321 || position->xpos == 384 && position->ypos == 319)
			{ dead = false; scared = false; engaged = false; sprite->setTex(defaultTex, 8); setVel(1, 0); set = true; }
		}
	}

	void engage() {
		if (!engaged) {
			if (position->xpos < 384) {
				velX = 1;
			}
			if (position->xpos > 384) {
				velX = -1;
			}
			if (position->ypos < 224) {
				velY = 1;
			}
			if (position->ypos > 224) {
				velY = -1;
			}
			if (position->xpos == 384 && position->ypos == 224 && !engaged || position->xpos == 384 && position->ypos == 225 && !engaged) { wandering = false; engaged = true; scared = false; setVel(-1, 0); }
		}
	}

	void wander(int y1,int y2) {
		if (!engaged && !dead && !scared && wandering) {
			if (ent->getComponent<PositionC>().ypos > y1 && wand == 0) {
				setVel(0,-1);
			}
			if (ent->getComponent<PositionC>().ypos == y1) {
				wand = 1;
			}
			if (ent->getComponent<PositionC>().ypos < y2 && wand == 1) {
				setVel(0, 1);
			}
			if (ent->getComponent<PositionC>().ypos == y2) {
				wand = 0;
			}
		}
	}

		void move(Collider& col, Entity& entB) {
			if (ent->getComponent<Collider>().collider.x == col.collider.x && ent->getComponent<Collider>().collider.y == col.collider.y && scared == false && dead == false && engaged == true) {
			double a = sqrt((pow((double)(ent->getComponent<PositionC>().xpos - 1) - entB.getComponent<PositionC>().xpos, 2)) + pow((double)ent->getComponent<PositionC>().ypos - entB.getComponent<PositionC>().ypos, 2)); //UP
			double b = sqrt((pow((double)(ent->getComponent<PositionC>().xpos + 1) - entB.getComponent<PositionC>().xpos, 2)) + pow((double)ent->getComponent<PositionC>().ypos - entB.getComponent<PositionC>().ypos, 2)); //DOWN
			double c = sqrt((pow((double)(ent->getComponent<PositionC>().ypos - 1) - entB.getComponent<PositionC>().ypos, 2)) + pow((double)ent->getComponent<PositionC>().xpos - entB.getComponent<PositionC>().xpos, 2)); //RIGHT
			double d = sqrt((pow((double)(ent->getComponent<PositionC>().ypos + 1) - entB.getComponent<PositionC>().ypos, 2)) + pow((double)ent->getComponent<PositionC>().xpos - entB.getComponent<PositionC>().xpos, 2)); //LEFT
			if (a < b && a <= c && a <= d && velX != 1) { velY = 0; velX = -1;}
			else if (b <= c && b <= d && velX != -1) { velY = 0; velX = 1;}
			else if (c < d && velY != 1) { velY = -1; velX = 0;}
			else if (velY != -1) { velY = 1; velX = 0;}
			}
			//else if (ent->getComponent<Collider>().collider.x == col.collider.x && ent->getComponent<Collider>().collider.y == col.collider.y && scared == true && dead == false && engaged == true) {
			//	double a = sqrt((pow((double)(ent->getComponent<PositionC>().xpos - 1) - ent->getComponent<PositionC>().xpos, 2)) + pow((double)ent->getComponent<PositionC>().ypos - entB.getComponent<PositionC>().ypos, 2)); //UP
			//	double b = sqrt((pow((double)(ent->getComponent<PositionC>().xpos + 1) - ent->getComponent<PositionC>().xpos, 2)) + pow((double)ent->getComponent<PositionC>().ypos - entB.getComponent<PositionC>().ypos, 2)); //DOWN
			//	double c = sqrt((pow((double)(ent->getComponent<PositionC>().ypos - 1) - ent->getComponent<PositionC>().ypos, 2)) + pow((double)ent->getComponent<PositionC>().xpos - entB.getComponent<PositionC>().xpos, 2)); //RIGHT
			//	double d = sqrt((pow((double)(ent->getComponent<PositionC>().ypos + 1) - ent->getComponent<PositionC>().ypos, 2)) + pow((double)ent->getComponent<PositionC>().xpos - entB.getComponent<PositionC>().xpos, 2)); //LEFT
			//	if (a < b && a <= c && a <= d && velX != -1) { velY = 0; velX = 1;}
			//	else if (b <= c && b <= d && velX != 1) { velY = 0; velX = -1;}
			//	else if (c < d && velY != -1) { velY = 1; velX = 0;}
			//	else if (velY != 1) { velY = -1; velX = 0;}
			//}
			else if (ent->getComponent<Collider>().collider.x == col.collider.x && ent->getComponent<Collider>().collider.y == col.collider.y && scared == true && dead == false && engaged == true) {
				randomMove(col);
			}
		}

		void collide(Collider& col, Entity& entB) {
			if (dead == false && engaged == true) {
				if (Collision::ATE(ent->getComponent<Collider>().collider, col.collider, 3) && ent->getComponent<Enemy>().velX == 1	//right ppy>epy
					&& entB.getComponent<PositionC>().ypos > ent->getComponent<PositionC>().ypos) {
					ent->getComponent<PositionC>().collided();
					collided = true;
					ent->getComponent<PositionC>().xpos += -3;
					ent->getComponent<Enemy>().setVel(0, 1);
				}
				else if (Collision::ATE(ent->getComponent<Collider>().collider, col.collider, 3) && ent->getComponent<Enemy>().velX == 1	//right ppy<epy
					&& entB.getComponent<PositionC>().ypos < ent->getComponent<PositionC>().ypos) {
					ent->getComponent<PositionC>().collided();
					collided = true;
					ent->getComponent<PositionC>().xpos += -3;
					ent->getComponent<Enemy>().setVel(0, -1);
				}
				else if (Collision::ATE(ent->getComponent<Collider>().collider, col.collider, 3) && ent->getComponent<Enemy>().velX == -1	//left ppy>epy
					&& entB.getComponent<PositionC>().ypos > ent->getComponent<PositionC>().ypos) {
					ent->getComponent<PositionC>().collided();
					collided = true;
					ent->getComponent<PositionC>().xpos += 3;
					ent->getComponent<Enemy>().setVel(0, 1);
				}
				else if (Collision::ATE(ent->getComponent<Collider>().collider, col.collider, 3) && ent->getComponent<Enemy>().velX == -1	//left ppy<epy
					&& entB.getComponent<PositionC>().ypos < ent->getComponent<PositionC>().ypos) {
					ent->getComponent<PositionC>().collided();
					collided = true;
					ent->getComponent<PositionC>().xpos += 3;
					ent->getComponent<Enemy>().setVel(0, -1);
				}
				else if (Collision::ATE(ent->getComponent<Collider>().collider, col.collider, 3) && ent->getComponent<Enemy>().velY == 1		//down ppx>epx
					&& entB.getComponent<PositionC>().xpos > ent->getComponent<PositionC>().xpos) {
					ent->getComponent<PositionC>().collided();
					collided = true;
					ent->getComponent<PositionC>().ypos += -3;
					ent->getComponent<Enemy>().setVel(1, 0);
				}
				else if (Collision::ATE(ent->getComponent<Collider>().collider, col.collider, 3) && ent->getComponent<Enemy>().velY == 1		//down ppx<epx
					&& entB.getComponent<PositionC>().xpos < ent->getComponent<PositionC>().xpos) {
					ent->getComponent<PositionC>().collided();
					collided = true;
					ent->getComponent<PositionC>().ypos += -3;
					ent->getComponent<Enemy>().setVel(-1, 0);
				}
				else if (Collision::ATE(ent->getComponent<Collider>().collider, col.collider, 3) && ent->getComponent<Enemy>().velY == -1	//up ppx>epx
					&& entB.getComponent<PositionC>().xpos > ent->getComponent<PositionC>().xpos) {
					ent->getComponent<PositionC>().collided();
					collided = true;
					ent->getComponent<PositionC>().ypos += 3;
					ent->getComponent<Enemy>().setVel(1, 0);
				}
				else if (Collision::ATE(ent->getComponent<Collider>().collider, col.collider, 3) && ent->getComponent<Enemy>().velY == -1	//up ppx<epx
					&& entB.getComponent<PositionC>().xpos < ent->getComponent<PositionC>().xpos) {
					ent->getComponent<PositionC>().collided();
					collided = true;
					ent->getComponent<PositionC>().ypos += 3;
					ent->getComponent<Enemy>().setVel(-1, 0);
				}
				else collided = false;
			}
			if (collided) {
				randomMove(col);
				collided = false;
			}
		}
};