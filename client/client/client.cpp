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
#include "InfoToSend.h"


class MyFramework : public Framework {

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		//width = WINDOW_WIDTH;
		//height = WINDOW_HEIGHT;
		//if (WINDOW_WIDTH == 0 && WINDOW_HEIGHT == 0)
		//	fullscreen = true;
		//else
		//	fullscreen = false;
		width = 320;
		height = 200;
		fullscreen = false;
	}

	virtual bool Init() {
		//map_manager = std::make_unique<MapCreator>();
		return true;
	}

	virtual void Close() {

	}

	virtual bool Tick() {
		drawTestBackground();
		//showCursor(false);

		//map_manager->DrawAll();
		////TODO
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		//map_manager->SetRot(x, y);
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		//keep_info->SetClick(button, isReleased);
	}

	virtual void onKeyPressed(FRKey k) {
		//keep_info->SetKey(k);
	}

	virtual void onKeyReleased(FRKey k) {
	}

	virtual const char* GetTitle() override
	{
		return "asteroids";
	}

private:

	//std::unique_ptr<MapCreator> map_manager;
	//std::unique_ptr<InfoToSend> keep_info;
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


		try
		{
			int oplimit = 1;
			AsyncTCPClient client(4);
			
			while (true) {
				for (int i = 0; i < oplimit; i++) {
					client.emulateLongComputationOp(10, "178.159.224.36", 3333, handler, 1);
				}

				Sleep(2000);
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
	//auto t2 = high_resolution_clock::now();
	//duration<double, std::milli> ms_double = t2 - t1;
	//std::cout << ms_double.count() << "ms\n";
	return 0;
}
