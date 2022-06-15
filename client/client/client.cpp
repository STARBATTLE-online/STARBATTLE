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


class MyFramework : public Framework {

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		if (WINDOW_WIDTH == 0 && WINDOW_HEIGHT == 0)
			fullscreen = true;
		else
			fullscreen = false;

		width = WINDOW_WIDTH;
		height = WINDOW_HEIGHT;

		map_manager = std::make_unique<MapCreator>();

	}

	virtual bool Init() {
		//map_manager = std::make_unique<MapCreator>();
		return true;
	}

	virtual void Close() {

	}

	virtual bool Tick() {
		map_manager->UpdateRequest();
		drawTestBackground();
		//showCursor(false);

		//map_manager->DrawAll();
		////TODO
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		map_manager->SetRot(x, y);
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		map_manager->SetClickToRequest(button, isReleased);
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

	std::unique_ptr<MapCreator> map_manager;
};
int main(int argc, char* argv[])
{
	setlocale(0, "");
	srand(time(NULL));

	
	std::thread t1([]() {
		while (true)
		{
			run(new MyFramework);

		}
	});

	std::thread t2([]() {

		int oplimit = 500;

		using std::chrono::high_resolution_clock;
		using std::chrono::duration_cast;
		using std::chrono::duration;
		using std::chrono::milliseconds;

		
		
		try
		{
			int oplimit = 1;
			AsyncTCPClient client(4);
			
			while (true) {
				auto t1 = high_resolution_clock::now();
				for (int i = 0; i < oplimit; i++) {

					client.emulateLongComputationOp(10, "178.159.224.36", 3333, handler, 1, request);

				}
				auto t2 = high_resolution_clock::now();
				duration<double, std::milli> ms_double = t2 - t1;
				double rest = 1000 / FRAMERATE - ms_double.count();
				Sleep(rest);
			}
			
		}
		catch (system::system_error& e)
		{
			std::cout << "Error occured! Error code = " << e.code()
				<< ". Message: " << e.what();

			std::cout << e.code().value() << std::endl;
		}
	   catch (...) {
	   }
		return 0;
	});
	

	t1.join();
	t2.join();
	
	//duration<double, std::milli> ms_double = t2 - t1;
	//std::cout << ms_double.count() << "ms\n";
	return 0;
}
