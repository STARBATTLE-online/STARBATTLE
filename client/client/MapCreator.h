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
		width = 13;
		height = 13;
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

	void AddEnemyShip(int x, int y, Rotation rot, int sprite_id) {
		ships.push_back(new EnemyShip(x, y, rot));		
	}

	void MapResize() {

	}

	void AddBigAsteroid(int x, int y) {
		asteroids.push_back(new BigAsteroid(x, y));
	}

	void AddSmallAsteroid(int x, int y) {
		asteroids.push_back(new SmallAsteroid(x, y));
	}

	void DrawAll() {
		
		background->Draw();
		//std::cout << asteroids.size() << std::endl;
		for (auto asteroid : asteroids)
		{
			if (asteroid->GetCenter().first > -100 && asteroid->GetCenter().first < WINDOW_WIDTH + 100 && asteroid->GetCenter().second > -100 && asteroid->GetCenter().second < WINDOW_HEIGHT + 100)
			{
				if (asteroid->GetName() == "BigAsteroid")
				{
					drawSprite(big_asteroid_sprite, asteroid->x(), asteroid->y());
				}
				else if (asteroid->GetName() == "SmallAsteroid")
				{
					drawSprite(small_asteroid_sprite, asteroid->x(), asteroid->y());
				}
			}			
		}
		for (auto bullet : bullets)
		{
			if (bullet->GetCenter().first > -100 && bullet->GetCenter().first < WINDOW_WIDTH + 100 && bullet->GetCenter().second > -100 && bullet->GetCenter().second < WINDOW_HEIGHT + 100)
			{
				drawSprite(bullet_sprite, bullet->x(), bullet->y());
			}

		}
		for (auto ship : ships)
		{
			if (ship->GetCenter().first > -100 && ship->GetCenter().first < WINDOW_WIDTH + 100 && ship->GetCenter().second > -100 && ship->GetCenter().second < WINDOW_HEIGHT + 100)
			{
				ship->Draw();
			}
		}
		main_hero.Draw();

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
		bullets.push_back(new Bullet(x, y));
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
	std::vector<Asteroid*> asteroids;
	std::vector<Ship*> ships;
	MainHeroShip main_hero;
	Sprite* big_asteroid_sprite = createSprite("data/big_asteroid.png");
	Sprite* small_asteroid_sprite = createSprite("data/small_asteroid.png");
	Sprite* bullet_sprite = createSprite("data/bullet.png");
	std::vector<Bullet*> bullets;
};
