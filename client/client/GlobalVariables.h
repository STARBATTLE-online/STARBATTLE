#pragma once
#include <atomic>
#include <string>
#include <map>

int WINDOW_WIDTH = 1920;
int WINDOW_HEIGHT = 1080;
int MAP_WIDTH = 1000;
int MAP_HEIGHT = 1000;
int NUM_ASTEROIDS_BIG = 5;
int NUM_ASTEROIDS_SMALL = 5;
int NUM_AMMO = 3;
double ABILITY_PROBABILITY = 0.5;
int WINDOW_X = 200;
int WINDOW_Y = 200;
int PERSONAL_ID_PUBLIC = 333;
int PERSONAL_ID_PRIVATE = 333;
int FRAMERATE = 100;

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


std::map<Rotation, Sprite*> engine_sprites;
std::map<Rotation, Sprite*> ship_sprites;
std::string request = "";