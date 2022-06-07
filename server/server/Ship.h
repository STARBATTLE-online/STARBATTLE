#pragma once
#include "MovableSprite.h"
#include "SuperPower.h"
#include "MapCreator.h"

class Ship : public MovableSprite
{
public:
	Ship() {};
	Ship(const char* sprite_path, double sprite_width, double sprite_height, int sprite_mass) {
		width = sprite_width;
		height = sprite_height;
	};
	virtual ~Ship() {};

	
	void SetRotation(Rotation rot) {
		rotation = rot;
	}

	void Move() override {
		global_y += y_speed;
		global_x += x_speed;
		Border();
		UseImpulse();

		for(auto bullet : bullets) {
			bullet->Move();
		}
		
		if (dynamic_cast<Shield*>(power))
		{
			power->SetCoordsByCenter(GetCenterGlobal().first, GetCenterGlobal().second);
		}		
	}

	virtual bool CheckCollision(HeadSprite* element) {

		if (element == this)
		{
			return 0;
		}
		else if (GetRadius() + element->GetRadius()
			>= sqrt(pow(GetCenterGlobal().first - element->GetCenterGlobal().first, 2)
				+ pow(GetCenterGlobal().second - element->GetCenterGlobal().second, 2)))
		{
			if (dynamic_cast<SuperPower*>(element))
			{
				power = element;
				return 1;
			}
			else
			{
				return 1;
			}
		}
		else
		{
			return 0;
		}
	}

	void PowersHandler() {
		if (dynamic_cast<Shield*>(power))
		{
			power->SetCoords(GetCenterGlobal().first - power->GetSize().first / 2, GetCenterGlobal().second - power->GetSize().second / 2);
		}
		else if (dynamic_cast<Rocket*>(power))
		{
			//	
		}
	}

	void UseImpulse() {		
		x_speed /= impulse;
		y_speed /= impulse;
		if (abs(x_speed) < control_impulse)
		{
			x_speed = 0;
		}
		if (abs(y_speed) < control_impulse)
		{
			y_speed = 0;
		}
	}

	void Shoot() {
		bullets.push_back(new Bullet(GetCoordsGlobal().first + GetSize().second / 2, GetCoordsGlobal().second + GetSize().first / 2));
	}

	void GetRotationByMouse(int x_mouse, int y_mouse) {
		//��� ���� ������� ������������ ����, ��� �� �����, ���� ������������ �������
		if (true) {
			if (true)
				SetRotation(Rotation::Left);
			else {
				if (true)
					SetRotation(Rotation::Top);
				else
					SetRotation(Rotation::Bottom);
			}
		}
		else {
			if (true)
				SetRotation(Rotation::Right);
			else {
				if (true)
					SetRotation(Rotation::Top);
				else
					SetRotation(Rotation::Bottom);
			}
		}
	}


	void MoveManual(FRKey k) {
		switch (k)
		{
		case FRKey::RIGHT:
			x_speed = -1 * engine_power_speed;
			break;
		case FRKey::LEFT:
			x_speed = engine_power_speed;
			break;
		case FRKey::DOWN:
			y_speed = -1 * engine_power_speed;
			break;
		case FRKey::UP:
			y_speed = engine_power_speed;
			break;
		default:
			break;
		}
	}

	void SetEnginePowerSpeed(double new_speed) {
		engine_power_speed = new_speed;
	}

	//��� �� "�����������". ���� �� ���� - ������
	void SendMouseMoveEvent(int x, int y) {
		GetRotationByMouse(x, y);
	};

	void SendKeyPressEvent(FRKey k) {
		MoveManual(k);
	};

protected:
	HeadSprite* power;  //?
	Rotation rotation;	
	double impulse = 1.01;
	double control_impulse = 0.01;
	double engine_power_speed = 2;
	std::vector<Bullet*> bullets;
};

//����� ����� ��� �����, ���� �� �������� �������
class Bullet : public MovableSprite
{
public:
	Bullet(int x, int y) {
		width = 13;
		height = 13;
		global_x = x;
		global_y = y;
	};
	~Bullet() {};

	void Border() override{
		if ((global_x + width / 2 >= MAP_WIDTH) 
			|| (global_x < (width / 2) * -1)
			|| (global_y + height / 2 >= MAP_HEIGHT)
			|| (global_y < (height / 2) * -1))
		{
			delete this;
		}
	}
};