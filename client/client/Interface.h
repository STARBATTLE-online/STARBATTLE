#pragma once
#include "HeadSprite.h"
#include "Framework.h"
#include <map>

class Interface;
class Reticle;

class Reticle : public HeadSprite
{
public:
	Reticle() {
		sprite_path = "data/reticle2.png";
		sprite = createSprite(sprite_path);		
		width = 63;
		height = 63;
	};
	~Reticle(){};

	void SetCoords(int new_x, int new_y) override {
		global_x = new_x - height / 2 + WINDOW_X;
		global_y = new_y - width / 2 + WINDOW_Y;
	}


	void SetSprite(const char* sprite_path) {
		sprite = createSprite(sprite_path);
	}

	void Draw() {
		drawSprite(sprite, x(), y());
	}

	const char* sprite_path;
	Sprite* sprite;
	
};


class MainMenu
{
public:
	MainMenu() {
		main_menu_background = createSprite("data/interface/main_menu/background.png");
		play_button = createSprite("data/interface/main_menu/play_button.png");
		about_button = createSprite("data/interface/main_menu/about_button.png");
		score_button = createSprite("data/interface/main_menu/score_button.png");
	};
	~MainMenu() {};


	void Draw() {
		drawSprite(main_menu_background, 0, 0);
		drawSprite(play_button, 830, 634);
		if (is_hover["score_button"])
		{
			drawSprite(score_button, 127, 935);
		}
		else
		{
			drawSprite(score_button, 127, 940);
		}
		if (is_hover["about_button"])
		{
			drawSprite(about_button, 1595, 926);
		}
		else
		{
			drawSprite(about_button, 1595, 931);
		}
	}

	bool IsStart(FRMouseButton button, int x, int y) {
		if (button == FRMouseButton::LEFT && x > 830 && x < 1091 && y > 634 && y < 924)
		{
			return true;
		}
		return false;
	}

public:
	
	const char* play_sprite_path = "data/interface/main_menu/play_button.png";
	Sprite* play_button;
	std::map <std::string, bool> is_hover;

private:

	Sprite* main_menu_background;
	Sprite* about_button;
	Sprite* score_button;

};



class Interface
{
public:
	Interface(){};
	~Interface(){};

	Reticle GetReticle() {
		return reticle;
	}

	void Draw() {
		if (!is_start_game)
		{
			menu.Draw();
		}
		reticle.SetCoords(mouse_x, mouse_y);
		reticle.Draw();
	}



	void SetMouseCoords(int x, int y) {
		mouse_x = x;
		mouse_y = y;
		const char* path = "data/reticle2_dark.png";
		const char* button_path = "data/interface/main_menu/play_button_hover.png";

		if (x > 830 && x < 1091 && y > 634 && y < 924)
		{
			if (path != reticle.sprite_path)
			{
				reticle.sprite_path = path;
				reticle.SetSprite(reticle.sprite_path);
			}
			if (button_path != menu.play_sprite_path)
			{
				menu.play_sprite_path = button_path;
				menu.play_button = createSprite(menu.play_sprite_path);

			}
		}
		else
		{
			if (path == reticle.sprite_path)
			{
				reticle.sprite_path = "data/reticle2.png";
				reticle.SetSprite(reticle.sprite_path);
			}
			if (button_path == menu.play_sprite_path)
			{
				menu.play_sprite_path = "data/interface/main_menu/play_button.png";
				menu.play_button = createSprite(menu.play_sprite_path);
			}
		}
		if (x > 127 && x < 320 && y > 940 && y < 985)
		{
			menu.is_hover["score_button"] = true;
		}
		else
		{
			menu.is_hover["score_button"] = false;
		}
		if (x > 1595 && x < 1793 && y > 931 && y < 985)
		{
			menu.is_hover["about_button"] = true;
		}
		else
		{
			menu.is_hover["about_button"] = false;
		}
	}

	bool StartGame(FRMouseButton button) {
		return menu.IsStart(button, mouse_x, mouse_y);
	}

protected:
	Reticle reticle;
	MainMenu menu;
	int mouse_x;
	int mouse_y;
};

//D:/Programming/STARBATTLE/client/client/data/interface/main_menu
