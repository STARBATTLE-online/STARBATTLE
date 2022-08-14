#pragma once
#include <string>
#include <algorithm>

#include "Framework.h"

enum class Color {
	white
};

enum class Transform {
	none,
	uppercase,
	lowercase
};

enum class Decoration { //not added
	none, 
	underline,
	overline,
	line_through
};

struct Symbol {
	Sprite* symbol;
	int height;
	int width;
};

class Text
{
public:
	Text() {
		for (int i = 32; i <= 126; i++)
		{
			alphabet_white_25[i].symbol = createSprite(("data/text/white/" + std::to_string(i) + ".png").c_str());
			alphabet_white_25[i].height = 27;
			alphabet_white_25[i].width = 22;
		}

	}
	~Text() {}
	
	void print( std::string& text,
				int x, int y,
				int font_size = 25,
				Color color = Color::white,
				int line_height = 27,
				int letter_spacing = 0,
				Transform text_transform = Transform::none,
				Decoration text_decoration = Decoration::none);
	
	void println(	std::string& text,
					int x, int y,
					int font_size,
					Color color,
					int letter_spacing);

	void println_white_25(	std::string& text,
							int x, int y,
							int letter_spacing);

private:
	std::map<char, Symbol> alphabet_white_25;
};

void Text::print(	std::string& text,
					int x, int y,
					int font_size,
					Color color,
					int line_height,
					int letter_spacing,
					Transform text_transform,
					Decoration text_decoration) {
	std::string temp = "";
	int i = 1;
	for (char& ch : text) {
		if (ch == '\n') {
			switch (text_transform)
			{
			case Transform::uppercase:
				std::transform(text.begin(), text.end(), text.begin(), ::toupper);
				break;
			case Transform::lowercase:
				std::transform(text.begin(), text.end(), text.begin(), ::tolower);
				break;
			default:
				break;
			}
			println(temp, x, y + (line_height * i), font_size, color, letter_spacing);
			i++;
		}
		else {
			temp += ch;
		}
	}
}

void Text::println(	std::string& text,
					int x, int y,
					int font_size,
					Color color,
					int letter_spacing) {
	if (color == Color::white)
	{
		if (font_size == 25)
		{
			println_white_25(text, x, y, letter_spacing);
		}
	}
}

void Text::println_white_25(std::string& text,
							int x, int y,
							int letter_spacing){
	for (char& ch : text) {
		if (alphabet_white_25.find(ch) != alphabet_white_25.end()) {
			drawSprite(alphabet_white_25[ch].symbol, x, y);
			x += alphabet_white_25[ch].width + letter_spacing;
		}
	}
}