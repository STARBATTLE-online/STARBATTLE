#pragma once
#include "HeadSprite.h"

class Background : public HeadSprite
{
public:
	Background() {
		sprite = createSprite("data/background_2.png");
		width = 1000;
		height = 1000;
	};
	~Background() {};

	void Draw() override {
		for (int i = 0; i < MAP_WIDTH / width; i++)
		{
			for (int j = 0; j < MAP_HEIGHT / height; j++)
			{
				for (int k = -1; k <= 1; k++)
				{
					for (int t = -1; t <= 1; t++)
					{
						int x = -1 * WINDOW_X/4 + i * width + MAP_WIDTH * k;
						int y = -1 * WINDOW_Y/4 + j * height + MAP_WIDTH * t ;

						drawSprite(sprite, x, y);
					}
				}
			}
		}
	}
};