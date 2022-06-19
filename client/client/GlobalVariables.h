#pragma once
#include <atomic>
#include <string>
#include <map>

int window_width = 1920;
int window_height = 1080;
int map_width = 1000;
int map_height = 1000;
int window_x = 200;
int window_y = 200;
int personal_id_public = 333;
int personal_id_private = 333;
int framerate = 60;
int tick_number = 1;
int my_score = 0;

std::atomic<bool> is_connected = 0;
std::atomic<bool> is_start_game = 0;
std::atomic<bool> is_game_over = 0;


enum class Rotation
{
	Top,
	Left,
	Bottom,
	Right
};


std::map<std::pair<int, Rotation>, Sprite*> engine_sprites;
std::map<std::pair<int, Rotation>, Sprite*> ship_sprites;
std::map<int, Sprite*> big_explosion_sprites;
std::map<int, Sprite*> small_explosion_sprites;
std::map<int, Sprite*> shield_sprites;
std::string request = "";