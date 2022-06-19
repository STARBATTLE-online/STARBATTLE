#pragma once
#include <mutex>

#include "Background.h"
#include "Asteroid.h"
#include "Ship.h"
#include "Interface.h"
#include "InfoToSend.h"
#include "InfoFromServer.h"

class Bullet : public HeadSprite
{
public:
	Bullet(int x, int y) {
		width = 20;
		height = 20;
		global_x = x;
		global_y = y;
	};
	~Bullet() {};
};

class MapCreator //�������� ����� ��������� �� �����
{
public:
	MapCreator() {
		
		background = new Background();
		keep_info = new InfoToSend();
		UpdateRequest();

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
		main_hero.SetCoords(x, y);
		main_hero.SetRotation(Rotation::Top);
		main_hero.SetSprite(path);

		WINDOW_X = main_hero.GetCenterGlobal().first - WINDOW_WIDTH / 2;
		WINDOW_Y = main_hero.GetCenterGlobal().second - WINDOW_HEIGHT / 2;
	}


	void DrawAll() {
		
		background->Draw();
		//std::cout << asteroids.size() << std::endl;
		for (auto& asteroid : asteroids)
		{
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					int x = asteroid.GetCenterGlobal().first + MAP_WIDTH * i - WINDOW_X;
					int y = asteroid.GetCenterGlobal().second + MAP_WIDTH *j - WINDOW_Y;
			
					if (x > -100 && x < WINDOW_WIDTH + 100 && y > -100 && y < WINDOW_HEIGHT + 100)
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
					int x = bullet.GetCenterGlobal().first + MAP_WIDTH * i - WINDOW_X;
					int y = bullet.GetCenterGlobal().second + MAP_WIDTH * j - WINDOW_Y;

					if (x > -100 && x < WINDOW_WIDTH + 100 && y > -100 && y < WINDOW_HEIGHT + 100)
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
					int x = ship.GetCenterGlobal().first + MAP_WIDTH * i - WINDOW_X;
					int y = ship.GetCenterGlobal().second + MAP_WIDTH * j - WINDOW_Y;

					if (x > -100 && x < WINDOW_WIDTH + 100 && y > -100 && y < WINDOW_HEIGHT + 100)
					{
						ship.DrawXY(x, y);
					}
				}
			}
			
		}
		main_hero.Draw();

		//inter.Draw();

	}

	/*if (asteroid->GetCenter().first > -100 && asteroid->GetCenter().first < WINDOW_WIDTH + 100 && asteroid->GetCenter().second > -100 && asteroid->GetCenter().second < WINDOW_HEIGHT + 100)
	{
		if (asteroid->GetName() == "BigAsteroid")
		{
			drawSprite(big_asteroid_sprite, asteroid->x(), asteroid->y());
		}
		else if (asteroid->GetName() == "SmallAsteroid")
		{
			drawSprite(small_asteroid_sprite, asteroid->x(), asteroid->y());
		}
	}*/

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
	MainHeroShip main_hero;
	Sprite* big_asteroid_sprite = createSprite("data/big_asteroid.png");
	Sprite* small_asteroid_sprite = createSprite("data/small_asteroid.png");
	Sprite* bullet_sprite = createSprite("data/bullet.png");
	std::vector<Bullet> bullets;
};
