#pragma once
#include "HeadSprite.h"

class Background : public HeadSprite
{
public:
	Background() {
		sprite = createSprite("data/background_3.png");
		width = 1000;
		height = 1000;
	};
	~Background() {};

	void Draw() {
		for (int i = 0; i < map_width / width; i++)
		{
			for (int j = 0; j < map_height / height; j++)
			{
				for (int k = -1; k <= 1; k++)
				{
					for (int t = -1; t <= 1; t++)
					{
						int x = -1 * window_x/4 + i * width + map_width * k;
						int y = -1 * window_y/4 + j * height + map_width * t ;

						drawSprite(sprite, x, y);
					}
				}
			}
		}
	}

	Sprite* sprite;
};