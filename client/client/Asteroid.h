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
			width = 68;
			height = 60;
		}
		else if (true)
		{
			width = 44;
			height = 36;
		}
		global_x = x;
		global_y = y;
		name = type;
	};

	virtual ~Asteroid() = default;


	AsteroidTypes name;
};


