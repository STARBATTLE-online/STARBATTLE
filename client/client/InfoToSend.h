#pragma once
#include "Framework.h"

class InfoToSend
{
public:
	InfoToSend(){};
	~InfoToSend(){};

	void AddID() {

	}

	void Update() {
		request.clear();
		request += std::to_string(PERSONAL_ID);
	}

	void SetCoords(int x, int y) {
		request += " mm "; // mouse move
		request += std::to_string(x);
		request += " ";
		request += std::to_string(y);

	}

	void SetKey(FRKey k) {
		request += " kb "; //keyboard buttom
		switch (k)
		{
		case FRKey::RIGHT:
			request += "r";
			break;
		case FRKey::LEFT:
			request += "l";
			break;
		case FRKey::DOWN:
			request += "d";
			break;
		case FRKey::UP:
			request += "u";
			break;
		default:
			break;
		}
	}

	void SetClick(FRMouseButton button, bool isReleased) {
		request += " mb "; //mouse buttom
		switch (button)
		{
		case FRMouseButton::LEFT:
			request += "l";
			break;
		case FRMouseButton::MIDDLE:
			request += "m";
			break;
		case FRMouseButton::RIGHT:
			request += "r";
			break;
		default:
			break;
		}
	}

};
