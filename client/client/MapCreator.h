#pragma once
#include "Background.h"
#include "Asteroid.h"
#include "Ship.h"
#include "Interface.h"
#include "InfoToSend.h"


class MapCreator //�������� ����� ��������� �� �����
{
public:
	MapCreator() {
		
		background = new Background();
		keep_info = new InfoToSend();
		UpdateRequest();

		for (int i = 0; i < NUM_ASTEROIDS(); i++)
		{
			if (i < NUM_ASTEROIDS() / 2)
			{
				asteroids.push_back(new BigAsteroid(rand() % MAP_WIDTH, rand() % MAP_HEIGHT, rand() % 10 - 5, rand() % 10 - 5));
			}
			else
			{
				asteroids.push_back(new SmallAsteroid(rand() % MAP_WIDTH, rand() % MAP_HEIGHT, rand() % 10 - 5, rand() % 10 - 5));
			}
		}



		main_hero.SetCoords(rand() % MAP_WIDTH, rand() % MAP_HEIGHT);


	};
	~MapCreator() {};


	void AddShip(int x, int y, Rotation rot) {

	}

	void MapResize() {

	}

	void AddAsteroid(int x, int y, Rotation rot) {
		asteroids.push_back(new BigAsteroid(rand() % MAP_WIDTH, rand() % MAP_HEIGHT, rand() % 10 - 5, rand() % 10 - 5));
	}

	void DrawAll() {
		background->Draw();
		for (auto astroid : asteroids)
		{
			astroid->Draw();
		}
		for (auto ship : ships)
		{
			ship->Draw();
		}
		main_hero.Draw();
		inter.Draw();
	}

	void SetRot(int x, int y) {
		main_hero.GetRotationByMouse(x, y);
		keep_info->SetCoords(x, y);
	}

	void SetKeyToRequest(FRKey k) {
		keep_info->SetKey(k);
	}

	void SetClickToRequest(FRMouseButton button, bool isReleased) {
		keep_info->SetClick(button, isReleased);
	}

	void UpdateRequest() {
		keep_info->Update();
	}

	

	//����������� ����������� ����� � ��������� ��������� ��� ������������� ����� �������
protected:
	std::vector<Asteroid*> asteroids;
	MainHeroShip main_hero;
	std::vector<Ship*> ships;
	Background* background;
	Interface inter;


	InfoToSend* keep_info;
};
