#pragma once
#include <mutex>

#include "Background.h"
#include "Asteroid.h"
#include "Ship.h"
#include "Interface.h"
#include "InfoToSend.h"
#include "InfoFromServer.h"


enum class ExplosionTypes {
	Big,
	Small
};

enum class PowerTypes {
	Shield,
	Rocket,
	Speed
};


class Bullet : public HeadSprite
{
public:
	Bullet(int x, int y) {
		width = 20;
		height = 20;
		SetCoordsByCenter(x, y);
	};
	~Bullet() override {};
};

class Explosion : public HeadSprite
{
public:
	Explosion(int x, int y, int start, ExplosionTypes type) {
		if (type == ExplosionTypes::Big)
		{
			width = 384;
			height = 384;
		}
		else if (true)
		{
			width = 200;
			height = 200;
		}
		SetCoordsByCenter(x, y);
		start_tick = start;
		name = type;
	};
	~Explosion() override {};
	int start_tick;
	ExplosionTypes name;
};

class Power : public HeadSprite
{
public:
	Power(int x, int y, PowerTypes type) {
		if (type == PowerTypes::Shield)
		{
			width = 126;
			height = 126;
			SetCoordsByCenter(x, y);
		}
		name = type;
	};
	~Power() override {};
	PowerTypes name;
};


class MapCreator //�������� ����� ��������� �� �����
{
public:
	MapCreator() {
		
		background = new Background();
		keep_info = new InfoToSend();
		UpdateRequest();

		big_explosion_sprites[1] = createSprite("data/ships/explosions/big/1.png");
		big_explosion_sprites[2] = createSprite("data/ships/explosions/big/2.png");
		big_explosion_sprites[3] = createSprite("data/ships/explosions/big/3.png");
		big_explosion_sprites[4] = createSprite("data/ships/explosions/big/4.png");
		big_explosion_sprites[5] = createSprite("data/ships/explosions/big/5.png");
		big_explosion_sprites[6] = createSprite("data/ships/explosions/big/6.png");
		big_explosion_sprites[7] = createSprite("data/ships/explosions/big/7.png");

		shield_sprites[1] = createSprite("data/ships/shields/1.png");
		shield_sprites[2] = createSprite("data/ships/shields/2.png");
		shield_sprites[3] = createSprite("data/ships/shields/3.png");


	};
	~MapCreator() {};

	void AddMainHero(int x, int y, int sprite_id) {
		const char* path = "data/ships/sprites/1/spaceship.png";
		/*switch (sprite_id)
		{
		case 1:
			path = "data/ships/sprites/1/spaceship.png";
			break;
		case 2:
			path = "data/ships/main_hero/2.png";
			break;
		case 3:
			path = "data/ships/main_hero/3.png";
			break;
		default:
			break;
		}*/
		main_hero.SetCoordsByCenter(x, y);
		main_hero.SetRotation(Rotation::Top);
		main_hero.SetSpriteById(sprite_id);

		window_x = main_hero.GetCenterGlobal().first - window_width / 2;
		window_y = main_hero.GetCenterGlobal().second - window_height / 2;
	}


	void DrawAll() {
		
		background->Draw();

		for (auto& power : powers)
		{
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					int x = power.xGlobal() + map_width * i - window_x;
					int y = power.yGlobal() + map_width * j - window_y;

					if (x > -buffer && x < window_width + buffer && y > -buffer && y < window_height + buffer)
					{
						if (power.name == PowerTypes::Shield)
						{
							drawSprite(small_shield_sprite, x, y);
						}
						////////
					}
				}
			}
		}
		//std::cout << asteroids.size() << std::endl;
		for (auto& asteroid : asteroids)
		{
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					int x = asteroid.xGlobal() + map_width * i - window_x;
					int y = asteroid.yGlobal() + map_width *j - window_y;
			
					if (x > -buffer && x < window_width + buffer && y > -buffer && y < window_height + buffer)
					{
						if (asteroid.name == AsteroidTypes::Big)
						{
							drawSprite(big_asteroid_sprite, x, y);
						}
						else if (asteroid.name == AsteroidTypes::Small)
						{
							drawSprite(small_asteroid_sprite, x, y);
						}
					}		
				}
			}
		}


		for (auto& bullet : bullets)
		{

			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					int x = bullet.xGlobal() + map_width * i - window_x;
					int y = bullet.yGlobal() + map_width * j - window_y;

					if (x > -buffer && x < window_width + buffer && y > -buffer && y < window_height + buffer)
					{
						drawSprite(bullet_sprite, x, y);
					}
				}
			}
		}
		for (auto& ship : ships)
		{
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					int x = ship.xGlobal() + map_width * i - window_x;
					int y = ship.yGlobal() + map_width * j - window_y;

					if (x > -buffer && x < window_width + buffer && y > -buffer && y < window_height + buffer)
					{
						ship.DrawXY(x, y);
					}
				}
			}
			
		}
		main_hero.Draw();
		std::cerr << tick_number << "\n";

		for (auto& explosion : explosions)
		{
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					int x = explosion.xGlobal() + map_width * i - window_x;
					int y = explosion.yGlobal() + map_width *j - window_y;
			
					if (x > -buffer && x < window_width + buffer && y > -buffer && y < window_height + buffer)
					{
						int temp = tick_number - explosion.start_tick;
						std::cerr << temp << "\n";
						if (temp >= 2 && temp <= 14)
						{
							if (explosion.name == ExplosionTypes::Big)
							{
								drawSprite(big_explosion_sprites[temp/2], x, y);
							}
							else if (explosion.name == ExplosionTypes::Small)
							{
								drawSprite(small_explosion_sprites[temp/2], x, y);
							}
						}
					}		
				}
			}
		}

		//inter.Draw();

	}

	void SetRot(int x, int y) {
		mouse_x = x;
		mouse_y = y;
		//std::cout<<mouse_x << " " << mouse_y<<std::endl;
		if (main_hero.GetRotationByMouse(mouse_x, mouse_y))
		{
			keep_info->SetCoords(mouse_x, mouse_y, main_hero.GetRotation());
		}
	}

	void SetKeyToRequest(FRKey k) {
		keep_info->SetKey(k);
	}

	void SetClickToRequest(FRMouseButton button, bool isReleased) {		
		keep_info->SetCoords(mouse_x, mouse_y, main_hero.GetRotation());
		keep_info->SetClick(button, isReleased);
	}

	void UpdateRequest() {
	}

	void Shoot(int x, int y) {
		bullets.push_back(Bullet(x, y));
	}

	//����������� ����������� ����� � ��������� ��������� ��� ������������� ����� �������
protected:
	Background* background;
	Interface inter;

	int mouse_x = 1;
	int mouse_y = 1;

	InfoToSend* keep_info;
	
public:
	std::mutex mt;
	std::vector<Asteroid> asteroids;
	std::vector<Ship> ships;
	std::vector<Explosion> explosions;
	std::vector<Power> powers;
	MainHeroShip main_hero;
	Sprite* big_asteroid_sprite = createSprite("data/big_asteroid.png");
	Sprite* small_asteroid_sprite = createSprite("data/small_asteroid.png");
	Sprite* bullet_sprite = createSprite("data/bullet.png");
	Sprite* small_shield_sprite = createSprite("data/ships/shield_icon_small.png");
	int buffer = 200;
	std::vector<Bullet> bullets;
	
};
