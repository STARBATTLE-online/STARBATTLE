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
				drawSprite(sprite, -1 * WINDOW_X + i * width, -1 * WINDOW_Y + j * height);
			}
		}
	}
};