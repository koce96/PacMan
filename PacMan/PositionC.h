#pragma once
#include "Components.h"
#include "Collision.h"

class PositionC : public Component {
private:


public:
	double xpos;		//MIND THE DOUBLES
	double ypos;
	double x() { return xpos; }
	double y() { return ypos; }
	int direction;
	double velocity;
	int height = 32;
	int width = 32;
	int scale = 1;
	double tempX, tempY;

	PositionC() {
		xpos = 0;
		ypos = 0;
	}

	PositionC(int sc) {
		xpos = 0;
		ypos = 0;
		scale = sc;
	}

	PositionC(double x, double y) {
		xpos = x;
		ypos = y;
	}
	PositionC(double x, double y, int h, int w, int sc) {
		xpos = x;
		ypos = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override {
		/*xpos = 0;
		ypos = 0;*/
		//velocity = 1;
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
		//xpos--;
		//ypos--;
		//cout << xpos << " " << ypos << endl;
		//cout << velocity << endl;
		velocity = 0.5;
	}

	void setPos(int x, int y) {
		/*xpos = x;
		ypos = y;*/
	}

	void x(double x) {
	/*	xpos = x;*/
	}

	void y(double y) {
	/*	ypos = y;*/
	}

	void collided() {
		/*ypos = ypos * -1;
		xpos = xpos * -1;*/
		
		//velocity = velocity * -1;
		xpos = tempX;
		ypos = tempY;
	}
	void saveXY() {
		tempX = xpos;
		tempY = ypos;
	}
};
