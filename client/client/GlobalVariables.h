#pragma once
#include <atomic>
#include <string>

inline int WINDOW_WIDTH = 1920;
inline int WINDOW_HEIGHT = 1080;
inline int MAP_WIDTH = 1000;
inline int MAP_HEIGHT = 1000;
inline int NUM_ASTEROIDS_BIG = 5;
inline int NUM_ASTEROIDS_SMALL = 5;
inline int NUM_AMMO = 3;
inline double ABILITY_PROBABILITY = 0.5;
inline double WINDOW_X = 200;
inline double WINDOW_Y = 200;
inline int PERSONAL_ID_PUBLIC = 333;
inline int PERSONAL_ID_PRIVATE = 333;
inline int FRAMERATE = 60;
std::atomic<bool> is_connected = 0;
std::atomic<bool> is_start_game = 0;

int NUM_ASTEROIDS() {
	return NUM_ASTEROIDS_BIG + NUM_ASTEROIDS_SMALL;
}

enum class Rotation
{
	Top,
	Left,
	Bottom,
	Right
};

std::string request = "";