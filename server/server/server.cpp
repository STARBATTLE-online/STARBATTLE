#define CURL_STATICLIB

#include <iostream>
#include <random>
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <iterator>
#include <regex>
#include <sstream>
#include <thread>

#include "Framework.h"
#include "GlobalVariables.h"
#include "MapCreator.h"
#include "boost_asio.h"

class MyFramework : public Framework {

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		//Тут было про окно, теперь не надо. Можно тут пускать буст или ещё что-то, подумай.
	}

	virtual bool Init() {

		map_manager = std::make_unique<MapCreator>();
		return true;
	}

	virtual void Close() {

	}

	virtual bool Tick() {
		showCursor(false);

		map_manager->CheckCollisionsAll();
		map_manager->MoveAll();

		//Это всё старое, ещё с перой версии.
		//Надо что-то такое, но под новые интерфейсы, этим всем занимается MapCreator, но вот условия проигрыша нигде нет вообще, надо сюда воткнуть, думаю.
		//И сделай расчёт на то, что добавим полосу XP, наверное...
		/*if (battleship->CheckCollision(asteroid))
		{
			std::cout << "Game over!" << "\n";
			return 1;
		}
		if (reticle->CheckShoot(asteroid, false) && asteroid->GetType() == "big")
		{
			asteroids_temp.push_back(new SmallAsteroid(asteroids, 0, -1.5, false, asteroid->GetCoords().first + 12, asteroid->GetCoords().second - 10));
			asteroids_temp.push_back(new SmallAsteroid(asteroids, 0, 1.5, false, asteroid->GetCoords().first + 12, asteroid->GetCoords().second + 35));
		}
		if (reticle->CheckShoot(asteroid, false) && asteroid->GetType() == "small")
		{
			if (static_cast<double>(rand()) / RAND_MAX >= 1 - ABILITY_PROBABILITY)
			{
				icons.push_back(new Shield(false, asteroid->GetCoords().first, asteroid->GetCoords().second));
			}
		}
	
			std::erase_if(asteroids, [this](Asteroid* a) -> bool {
				return reticle->CheckShoot(a); });
			for (auto asteroid : asteroids_temp)
			{
				asteroids.push_back(asteroid);
			}
			for (auto icon : icons)
			{
				icon->Draw();
				icon->MoveCheck();
			}
			std::erase_if(icons, [this](Icon* i) -> bool {
				return battleship->CheckCollisionIcon(i); });
			for (auto asteroid : asteroids)
			{
				asteroid->MoveCheck();
			}

			battleship->Draw();
			reticle->Draw();
			return false;*/


	}

	virtual const char* GetTitle() override
	{
		return "asteroids";
	}
private:

	std::unique_ptr<MapCreator> map_manager;

	//Старая строка, но, кстати, icons ещё нигде нет, надо добавить.
	//И тебе и мне. Это всякие иконки типа щита, которые выпадают из астероидов
	//std::vector<Icon*> icons;
};

const unsigned int DEFAULT_THREAD_POOL_SIZE = 2; // для буста

int main()
{
	srand(time(NULL));

	
	unsigned short port_num = 3333; 


	std::thread t1([]() {
		while (true)
		{
			run(new MyFramework);
		}
		});

	std::thread t2([]() {
		try
		{
			//it instantiates an object of the Server class named srv.
			Server srv;

			//before starting the server, the optimal size of the pool is calculated.
			// The general formula often used in parallel applications to find the optimal number of threads is the number of processors the computer has multiplied by 2.
			// We use the std::thread::hardware_concurrency() static method to obtain the number of processors. 
			unsigned int thread_pool_size =
				std::thread::hardware_concurrency() * 2;

			//because this method may fail to do its job returning 0,
			// we fall back to default value represented by the constant DEFAULT_THREAD_POOL_SIZE, which is equal to 2 in our case.
			if (thread_pool_size == 0)
				thread_pool_size = DEFAULT_THREAD_POOL_SIZE;

			srv.Start(port_num, thread_pool_size);

			std::this_thread::sleep_for(std::chrono::seconds(60));

			srv.Stop();
		}
		catch (system::system_error& e)
		{
			std::cout << "Error occured! Error code = "
				<< e.code() << ". Message: "
				<< e.what();
		}
		});

	t1.join();
	t2.join();

	return 0;
}
