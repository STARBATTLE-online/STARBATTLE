#pragma once
#include <mutex>

#include "Background.h"
#include "Asteroid.h"
#include "Ship.h"
#include "Interface.h"
#include "InfoToSend.h"
#include "InfoFromServer.h"


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
		for (auto astroid : asteroids)
		{
			astroid->Draw();
		}
		for (auto ship : ships)
		{
			ship->Draw();
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
};
