#pragma once
#include "HeadSprite.h"
#include "SuperPower.h"
#include <map>

bool fix = false;


class Ship : public HeadSprite
{
public:
	Ship() {};
	Ship(int sprite_width, int sprite_height, int sprite_mass) {
		width = sprite_width;
		height = sprite_height;
	};
	virtual ~Ship() {};


	void SetRotation(Rotation rot) {
		rotation = rot;
	}


	Rotation GetRotation() {
		return rotation;
	}

	void PowersHandler(int x, int y) {
		if (dynamic_cast<Shield*>(power))
		{
			power->SetCoords(x, y);
		}
		else if (dynamic_cast<Rocket*>(power))
		{
			//	
		}
	}


	void Draw() {
		
		drawSprite(ship_sprites[{sprite_id, rotation}], x(), y());
		if (is_engine)
		{
			//drawSprite(engine_sprites[rotation], x() - (engine_width - width) / 2, y() - (engine_height - height) / 2);
			drawSprite(engine_sprites[{sprite_id, rotation}], (x() - ((engine_width - width) / 2)), (y() - ((engine_height - height) / 2)));
		}
		if (power)
		{
			//power->Draw();
		}
	}

	void DrawXY(int x, int y){
		drawSprite(ship_sprites[{sprite_id, rotation}], x, y);
		if (is_engine)
		{
			//drawSprite(engine_sprites[rotation], x() - (engine_width - width) / 2, y() - (engine_height - height) / 2);
			drawSprite(engine_sprites[{sprite_id, rotation}], (x - ((engine_width - width) / 2)), (y - ((engine_height - height) / 2)));
		}
		
		if (power)
		{
			//power->Draw();
		}
	}

	void SetEngine(bool flag) {
		is_engine = flag;
	}


	int sprite_id;


protected:
	HeadSprite* power = nullptr;  //?
	Rotation rotation;
	int engine_width;
	int engine_height;
	bool is_engine = false;

};

class MainHeroShip : public Ship
{
public:
	MainHeroShip(int id = 4) {
		sprite_id = id;

		rotation = Rotation::Top;
		width = 192;
		height = 192;
		engine_width = 424;
		engine_height = 424;
	};
	~MainHeroShip() {};

	bool GetRotationByMouse(int x_mouse, int y_mouse) {
		Rotation temp_rot = rotation;
		if (x_mouse <= window_width / 2) {
			if (abs(x_mouse - window_width / 2) > abs(y_mouse - window_height / 2))
				SetRotation(Rotation::Left);
			else {
				if (y_mouse <= window_height / 2)
					SetRotation(Rotation::Top);
				else
					SetRotation(Rotation::Bottom);
			}
		}
		else {
			if (abs(x_mouse - window_width / 2) > abs(y_mouse - window_height / 2))
				SetRotation(Rotation::Right);
			else {
				if (y_mouse <= window_height / 2)
					SetRotation(Rotation::Top);
				else
					SetRotation(Rotation::Bottom);
			}
		}

		if (temp_rot!= rotation)
		{
			return 1;
		}
		return 0;
	}


private:
};

class EnemyShip : public Ship
{
public:
	EnemyShip(int x, int y, Rotation rot, int id = 3) {
		sprite_id = id;
		width = 192;
		height = 192;
		SetRotation(rot);
		SetCoordsByCenter(x, y);
		engine_width = 424;
		engine_height = 424;
	};
	~EnemyShip() {};

private:

};


