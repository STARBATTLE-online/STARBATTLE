#pragma once
#include <iostream>
#include <vector>
#include "Framework.h"
#include "GlobalVariables.h"

class HeadSprite {
public:
	HeadSprite() {
		height = 0;
		width = 0;
		sprite = NULL;
	};
	HeadSprite(const char* sprite_path, double sprite_width, double sprite_height) : width(sprite_width), height(sprite_height) {
		sprite = createSprite(sprite_path);
	};

	virtual ~HeadSprite() {};

	void SetImage(const char* sprite_path) {
		sprite = createSprite(sprite_path);
	};

	virtual void SetCoords(double new_x, double new_y) {
		global_x = new_x;
		global_y = new_y;
	}

	virtual void SetCoordsByCenter(double new_x, double new_y) {
		global_x = new_x - width / 2;
		global_y = new_y - height / 2;
	}

	virtual void Draw() {
		drawSprite(sprite, x(), y());
	}

	std::pair<double, double> GetCenterGlobal() {
		return std::make_pair(global_x + width / 2, global_y + height / 2);
	}

	double xGlobal() {
		return global_x;
	}

	double yGlobal() {
		return global_y;
	}

	double x() {
		return global_x - WINDOW_X;
	}

	double y() {
		return global_y - WINDOW_Y;
	}

	virtual std::string GetName() {
		return "HeadSprite";
	}

protected:
	Sprite* sprite;
	double width;
	double height;
	double global_x;
	double global_y;
};
