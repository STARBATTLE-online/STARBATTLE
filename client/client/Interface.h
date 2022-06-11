#pragma once
#include "HeadSprite.h"

class Interface;
class Reticle;

class Reticle : public HeadSprite
{
public:
	Reticle() {
		sprite = createSprite("data/reticle2.png");
		width = 65;
		height = 64;
	};
	~Reticle();

	void SetCoords(double new_x, double new_y) override {
		global_x = new_x - height / 2 + WINDOW_X;
		global_y = new_y - width / 2 + WINDOW_Y;
	}

	void SendMouseMoveEvent(int x, int y) {
		SetCoords(x, y);
	};




private:

};

class Interface
{
public:
	Interface();
	~Interface();

	Reticle GetReticle() {
		return reticle;
	}

	void Draw() {
		reticle.Draw();
	}

private:
	Reticle reticle;
};

