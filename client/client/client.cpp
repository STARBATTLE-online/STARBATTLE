#include "Framework.h"
#include "boost_asio.h"

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

#include "GlobalVariables.h"

#include "MapCreator.h"
#include "Interface.h"
#undef main

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

class MyFramework : public Framework {

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		if (window_width == 0 && window_height == 0)
			fullscreen = true;
		else
			fullscreen = false;

		width = window_width;
		height = window_height;

	}

	virtual bool Init() {
		map_manager = std::make_shared<MapCreator>();
		inter = std::make_shared<Interface>();
		InfoFromServer::SetMapCreator(map_manager);
		return true;
	}

	virtual void Close() {

	}

	virtual bool Tick() {
	
		if (exit_game)
		{
			map_manager->SetClosed();
			Close();
			return true;
		}
		auto t1 = high_resolution_clock::now();
		if (rest > 0)
		{
			Sleep(rest);
		}
		std::lock_guard<std::mutex> lock(map_manager->mt);
		
		if (!is_start_game || is_game_over)
		{
			death_ticks = 0;
			
			inter->Draw();
			showCursor(false);
		}
		else if (is_start_game && !is_connected)
		{
			Sprite* load = createSprite("data/interface/connecting.png");
			drawSprite(load, 0, 0);

			inter->Draw();
			showCursor(false);

		}
		else if (is_connected && !is_game_over)
		{
			//drawTestBackground();
			showCursor(false);			
			
			map_manager->DrawAll();
			inter->Draw();

		}
		auto t2 = high_resolution_clock::now();
		duration<double, std::milli> ms_double = t2 - t1;
		rest = 1000 / framerate - ms_double.count();
		//////std::cout << "ms_double " << ms_double << " rest " << rest << std::endl;
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		if (!is_start_game)
		{
			inter->SetMouseCoords(x, y);
		}
		else
		{
			map_manager->SetRot(x, y);
			inter->SimpleSetMouseCoords(x, y);
		}
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		
		if (!is_start_game)
		{
			if (isReleased)
			{
				inter->ButtonClick(button);
			}
		}
		else
		{
			if (is_start_game && is_connected)
			{
				if (isReleased)
				{
					if (inter->IsCross(button))
					{

						is_game_over = 1;
						is_start_game = 0;
						is_connected = 0;
						map_manager->SetClosed();
						se.playMusicEffect(0);
						
					}
				}

			}
			map_manager->SetClickToRequest(button, isReleased);
		}
	}

	virtual void onKeyPressed(FRKey k) {
		map_manager->SetKeyToRequest(k);
	}

	virtual void onKeyReleased(FRKey k) {
		
	}

	virtual const char* GetTitle() override
	{
		return "asteroids";
	}

private:
	double rest = 0;
	std::shared_ptr<MapCreator> map_manager;
	std::shared_ptr<Interface> inter;
};
int main(int argc, char* argv[])
{
	setlocale(0, "");
	srand(time(NULL));
	se.addSoundEffect(".\\data\\music\\menu_music.wav");		//0
	se.addSoundEffect(".\\data\\music\\game_music.wav");		//1
	se.addSoundEffect(".\\data\\music\\another_sound.wav");		//2
	se.addSoundEffect(".\\data\\music\\powerup_sound.wav");		//3
	se.addSoundEffect(".\\data\\music\\shoot_sound.wav");		//4
	se.addSoundEffect(".\\data\\music\\spawn_sound.wav");		//5
	se.addSoundEffect(".\\data\\music\\damage_sound.wav");		//6
	se.playMusicEffect(0);



	
	std::thread t1([]() {
		run(new MyFramework);
		exit_game = true;
		return 0;
	});

	std::thread t2([]() {
		while (!is_start_game)
		{
			Sleep(100);
		}

		try
		{
			AsyncTCPClient client(1);
			while (!exit_game)
			{
				while (!is_start_game)
				{
					Sleep(100);
				}

				client.emulateLongComputationOp(10, "178.159.224.36", 3333, handler, 1, "INIT");
				while (!is_connected)
				{
					Sleep(100);
				}
				se.playMusicEffect(1);
			
				//////std::cout << request << std::endl;
				client.emulateLongComputationOp(10, "178.159.224.36", 3333, handler, 1, request);
				request = "TICK";
				while (is_connected) {
					auto t1 = high_resolution_clock::now();	
						//////std::cout << request << std::endl;
					client.emulateLongComputationOp(1, "178.159.224.36", 3333, handler, 1, request);
					request = "TICK";
					auto t2 = high_resolution_clock::now();
					duration<double, std::milli> ms_double = t2 - t1;
					double rest = 1000 / framerate - ms_double.count();
					//////std::cout << "boost rest " << rest << std::endl;

					Sleep(rest);
				}
				if (is_game_over == 1 &&
					is_start_game == 0 &&
					is_connected == 0)
				{
					client.emulateLongComputationOp(1, "178.159.224.36", 3333, handler, 1, request);
				}
			}
			client.close();
			return 0;
			
		}
		catch (system::system_error& e)
		{
			////std::cout << "Error occured! Error code = " << e.code()				<< ". Message: " << e.what();

			////std::cout << e.code().value() << std::endl;
		}
	   catch (...) {
	   }
		return 0;
	});
	

	t1.join();
	t2.join();
	
	//duration<double, std::milli> ms_double = t2 - t1;
	//////std::cout << ms_double.count() << "ms\n";
	return 0;
}
