#pragma once
#include "HeadSprite.h"

//Тут буду добавлять ещё способности. Но логику буду тебя просить писать))
//На счёт траектории ракеты пока думаю, может сам попробую сделать.
//Но в основном буду рисовать спрайты и присобачивать в интерфейс.
class SuperPower : public HeadSprite
{
public:
	SuperPower() {};
	
	~SuperPower(){};

private:

};

class SuperPowerIcon : public HeadSprite
{
public:
	SuperPowerIcon();
	~SuperPowerIcon();

private:

};


//Где-то надо сделать вызов этого дела по нажатию кнопки (включение щита).
//Он должен быть ввиден всем, так что это тоже через сервер. Ну и надо условие прописать, что если щит, то не корабль неуязвим.
//Ещё где-то было коллизия щита в старом проекте, но она калечная.
//Там в условии было типа сделайте так, чтоб объекты пролетали, а не отскакивали.
//Лучше или отбивать их как астероиды, наверное, или вообще взрывать нафиг всё, к чему щит притронется))
class Shield : public SuperPower
{
public:
	Shield(){
		width = 63;
		height = 63;
		shield_duration = 80;
		start_time = getTickCount();
	};
	~Shield(){};

private:
	unsigned int shield_duration;
	unsigned int start_time;
	std::vector<const char*> frames;
};

class Rocket : public SuperPower
{
public:
	Rocket(){};
	~Rocket(){};

private:

};