#pragma once
#include "HeadSprite.h"
#include "SuperPower.h"
#include <map>


class Bullet : public HeadSprite
{
public:
	Bullet(int x, int y) {
		sprite = createSprite("data/bullet.png");
		width = 13;
		height = 13;
		global_x = x;
		global_y = y;
	};
	~Bullet() {};

};

class Ship : public HeadSprite
{
public:
	Ship() {};
	Ship(const char* sprite_path, int sprite_width, int sprite_height, int sprite_mass) {
		sprite = createSprite(sprite_path);
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

	void SetSprite(const char* sprite_path) {
		SetImage(sprite_path);
	}

	void Draw() override {
		drawSprite(ship_sprites[rotation], x(), y());
		if (power)
		{
			power->Draw();
		}
		for (auto bullet : bullets)
		{
			bullet->Draw();
		}

	}


	void Shoot(int x, int y) {
		bullets.push_back(new Bullet(x, y));
	}

protected:
	HeadSprite* power = nullptr;  //?
	Rotation rotation;
	std::vector<Bullet*> bullets;
	Sprite* engine;

	std::map<Rotation, Sprite*> ship_sprites;

};

class MainHeroShip : public Ship
{
public:
	MainHeroShip() {
		ship_sprites[Rotation::Left] = createSprite("data/ships/sprites/1/spaceship_l.png");
		ship_sprites[Rotation::Right] = createSprite("data/ships/sprites/1/spaceship_r.png");
		ship_sprites[Rotation::Top] = createSprite("data/ships/sprites/1/spaceship.png");
		ship_sprites[Rotation::Bottom] = createSprite("data/ships/sprites/1/spaceship_b.png");

		rotation = Rotation::Top;
		sprite = ship_sprites[rotation];
		engine = createSprite("data/ships/main_hero/engine.png");
		width = 48;
		height = 48;
	};
	~MainHeroShip() {};

	bool GetRotationByMouse(int x_mouse, int y_mouse) {
		Rotation temp_rot = rotation;
		if (x_mouse <= WINDOW_WIDTH / 2) {
			if (abs(x_mouse - WINDOW_WIDTH / 2) > abs(y_mouse - WINDOW_HEIGHT / 2))
				SetRotation(Rotation::Left);
			else {
				if (y_mouse <= WINDOW_HEIGHT / 2)
					SetRotation(Rotation::Top);
				else
					SetRotation(Rotation::Bottom);
			}
		}
		else {
			if (abs(x_mouse - WINDOW_WIDTH / 2) > abs(y_mouse - WINDOW_HEIGHT / 2))
				SetRotation(Rotation::Right);
			else {
				if (y_mouse <= WINDOW_HEIGHT / 2)
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

	//void SetRotSprite() {
	//	switch (rotation)
	//	{
	//	case Rotation::Top:
	//		SetImage("data/ships/sprites/1/spaceship.png");
	//		//power->SetImage("data/spaceship_power.png");

	//		break;
	//	case Rotation::Left:
	//		SetImage("data/ships/sprites/1/spaceship_l.png");
	//		//power->SetImage("data/spaceship_power_l.png");

	//		break;
	//	case Rotation::Bottom:
	//		SetImage("data/ships/sprites/1/spaceship_b.png");
	//		//power->SetImage("data/spaceship_power_b.png");

	//		break;
	//	case Rotation::Right:
	//		SetImage("data/ships/sprites/1/spaceship_r.png");
	//		//power->SetImage("data/spaceship_power_r.png");
	//		break;
	//	default:
	//		break;
	//	}
	//}

	void SendMouseMoveEvent(int x, int y) {
		GetRotationByMouse(x, y);
	};





private:
};

class EnemyShip : public Ship
{
public:
	EnemyShip(int x, int y, Rotation rot) {

		ship_sprites[Rotation::Left] = createSprite("data/ships/sprites/3/spaceship_l.png");
		ship_sprites[Rotation::Right] = createSprite("data/ships/sprites/3/spaceship_r.png");
		ship_sprites[Rotation::Top] = createSprite("data/ships/sprites/3/spaceship.png");
		ship_sprites[Rotation::Bottom] = createSprite("data/ships/sprites/3/spaceship_b.png");
		
		sprite = createSprite("data/ships/enemy/spaceship.png");
		width = 48;
		height = 48;
		SetRotation(rot);
		global_x = x;
		global_y = y;
	};
	~EnemyShip() {};

private:

};


