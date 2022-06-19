#pragma once
#pragma once
#include "HeadSprite.h"

enum class AsteroidTypes {
	Big,
	Small
};

class Asteroid : public HeadSprite
{
public:
	Asteroid() {};
	Asteroid(int x, int y, AsteroidTypes type){
		if (type == AsteroidTypes::Big)
		{
			width = 136;
			height = 120;
		}
		else if (true)
		{
			width = 88;
			height = 72;
		}
		global_x = x;
		global_y = y;
		name = type;
	};

	virtual ~Asteroid() = default;


	AsteroidTypes name;
};


