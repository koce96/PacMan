#pragma once
#include "Components.h"
#include "Collision.h"

class PositionC : public Component {
private:

public:
	int xpos;	
	int ypos;
	int x() { return xpos; }
	int y() { return ypos; }
	int direction;
	int velocity;
	int height = 32;
	int width = 32;
	int scale = 1;
	int tempX, tempY;

	PositionC() {
		xpos = 0;
		ypos = 0;
	}

	PositionC(int sc) {
		xpos = 0;
		ypos = 0;
		scale = sc;
	}

	PositionC(int x, int y) {
		xpos = x;
		ypos = y;
	}
	PositionC(int x, int y, int h, int w, int sc) {
		xpos = x;
		ypos = y;
		height = h;
		width = w;
		scale = sc;
		tempX;
		tempY;
	}

	void init() override {
	}

	void update() override {
		if (direction == 1) {
			ypos -= velocity;
			xpos = xpos;
		}
		if (direction == 2) {
			ypos += velocity;
			xpos = xpos;
		}
		if (direction == 3) {
			ypos = ypos;
			xpos -= velocity;
		}
		if (direction == 4) {
			ypos = ypos;
			xpos += velocity;
		}
		velocity = 1;
	}

	void setPos(int x, int y) {
	}

	void x(double x) {
	}

	void y(double y) {
	}

	void collided() {
		xpos = tempX;
		ypos = tempY;
	}
	void saveXY() {
		tempX = xpos;
		tempY = ypos;
	}
};