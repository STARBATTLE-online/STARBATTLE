#pragma once
#pragma once
#include "HeadSprite.h"


class Asteroid : public HeadSprite
{
public:
	Asteroid() {};
	Asteroid(const char* sprite_path, int sprite_width, int sprite_height, int sprite_mass) {
		sprite = createSprite(sprite_path);
		width = sprite_width;
		height = sprite_height;
	};

	virtual ~Asteroid() {};


};

class BigAsteroid : public Asteroid
{
public:
	BigAsteroid(int x, int y) {
		sprite = createSprite("data/big_asteroid.png"); // легковес!!
		width = 68;
		height = 60;
		SetCoordsByCenter(x, y);
	};
	
	std::string GetName() override {
		return "BigAsteroid";
	}


private:

};

class SmallAsteroid : public Asteroid
{
public:
	SmallAsteroid(int x, int y) {
		sprite = createSprite("data/small_asteroid.png");// легковес!!
		width = 44;
		height = 36;
		SetCoordsByCenter(x, y);
	};

	std::string GetName() {
		return "SmallAsteroid";
	}


private:

};

