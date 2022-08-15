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
	int height = 27;
	int width = 18;
};

class Text
{
public:
	Text() {
		
		for (int i = 32; i <= 126; i++)
		{
			alphabet_white_25[i].symbol = createSprite(("data/text/white/" + std::to_string(i) + ".png").c_str());
			if (i == 32 || i == 43 || i == 52 || i == 54 || i == 97 || i == 16 || i == 110 ||
				i == 65 || i == 70 || i == 75 || i == 76 || i == 83 || i == 95 || i == 112)
			{
				alphabet_white_25[i].width = 16;
			}
			else if (i == 33 || i == 39 || i == 44 || i == 46 || i == 105 || i == 108 || i == 124)
			{
				alphabet_white_25[i].width = 5;
			}
			else if (i == 34 || i == 36 || i == 47 || i == 48 || i == 50 || i == 92 || i == 100 || i == 102 ||
				i == 51 || i == 55 || i == 56 || i == 57 || i == 61 || i == 63 || i == 94 || i == 101 ||
				i == 103 || i == 104 || i == 107 || i == 111 || i == 113 || i == 117 || i == 121 || i == 122)
			{
				alphabet_white_25[i].width = 15;
			}
			else if (i == 35 || i == 38 || i == 53 || i == 66 || i == 84 || i == 85 || i == 86 || i == 87 ||
				i == 68 || i == 69 || i == 72 || i == 77 || i == 78 || i == 80 || i == 88 || i == 89 ||
				i == 90 || i == 98 || i == 118 || i == 120 || i == 126)
			{
				alphabet_white_25[i].width = 18;
			}
			else if (i == 37)
			{
				alphabet_white_25[i].width = 22;
			}
			else if (i == 40 || i == 41 || i == 42 || i == 49 || i == 60 || i == 62)
			{
				alphabet_white_25[i].width = 11;
			}
			else if (i == 45 || i == 73 || i == 116 || i == 123 || i == 125)
			{
				alphabet_white_25[i].width = 10;
			}
			else if (i == 58 || i == 59)
			{
				alphabet_white_25[i].width = 7;
			}
			else if (i == 64 || i == 109)
			{
				alphabet_white_25[i].width = 24;
			}
			else if (i == 67 || i == 71 || i == 119)
			{
				alphabet_white_25[i].width = 19;
			}
			else if (i == 74)
			{
				alphabet_white_25[i].width = 13;
			}
			else if (i == 79 || i == 81 || i == 82)
			{
				alphabet_white_25[i].width = 21;
			}
			else if (i == 91 || i == 93 || i == 96)
			{
				alphabet_white_25[i].width = 8;
			}
			else if (i == 106 || i == 114 || i == 115)
			{
				alphabet_white_25[i].width = 13;
			}
		}
	}
	~Text() {}
	
	void print( std::string text,
				int x, int y,
				int font_size = 25,
				Color color = Color::white,
				int line_height = 27,
				int letter_spacing = 0,
				Transform text_transform = Transform::none,
				Decoration text_decoration = Decoration::none);
	
	void println(	std::string text,
					int x, int y,
					int font_size,
					Color color,
					int letter_spacing);

	void printlnWhite25(std::string& text,
		int x, int y,
		int letter_spacing);

private:
	std::map<char, Symbol> alphabet_white_25;
};

void Text::print(	std::string text,
					int x, int y,
					int font_size,
					Color color,
					int line_height,
					int letter_spacing,
					Transform text_transform,
					Decoration text_decoration) {
	std::string temp = "";
	int i = 0;
	for (char ch : text) {
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
	if (text[text.size() - 1] != '\n')
	{
		println(temp, x, y + (line_height * i), font_size, color, letter_spacing);
	}
	
}

void Text::println(	std::string text,
					int x, int y,
					int font_size,
					Color color,
					int letter_spacing) {
	if (color == Color::white)
	{
		if (font_size == 25)
		{
			printlnWhite25(text, x, y, letter_spacing);
		}
	}
}

void Text::printlnWhite25(std::string& text,
	int x, int y,
	int letter_spacing) {
	for (char& ch : text) {
		if (alphabet_white_25.find(ch) != alphabet_white_25.end()) {
			drawSprite(alphabet_white_25[ch].symbol, x, y);
			x += alphabet_white_25[ch].width + letter_spacing;
		}
	}
}


