#pragma once
#include "GlobalVariables.h"
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
		request += "TICK";
		
	}

	void SetCoords(int x, int y, Rotation rot) {
		request += " MM "; // mouse move
		request += std::to_string(int(x + WINDOW_X));
		request += " ";
		request += std::to_string(int(y + WINDOW_Y));
		request += " ";
		switch (rot)
		{
		case Rotation::Top:
			request += 'T';
			break;
		case Rotation::Left:
			request += 'L';			
			break;
		case Rotation::Bottom:
			request += 'B';
			break;
		case Rotation::Right:
			request += 'R';
			break;
		default:
			break;
		}
		
		request += " " + std::to_string(PERSONAL_ID_PUBLIC) + " ";
		request += std::to_string(PERSONAL_ID_PRIVATE);
	}

	void SetKey(FRKey k) {
		request += " KB "; //keyboard buttom
		switch (k)
		{
		case FRKey::RIGHT:
			request += "R";
			break;
		case FRKey::LEFT:
			request += "L";
			break;
		case FRKey::DOWN:
			request += "D";
			break;
		case FRKey::UP:
			request += "U";
			break;
		default:
			break;
		}
		request += " " + std::to_string(PERSONAL_ID_PUBLIC) + " ";
		request += std::to_string(PERSONAL_ID_PRIVATE);
	}

	void SetClick(FRMouseButton button, bool isReleased) {
		request += " MB "; //mouse buttom
		switch (button)
		{
		case FRMouseButton::LEFT:
			request += "L";
			break;
		case FRMouseButton::MIDDLE:
			request += "M";
			break;
		case FRMouseButton::RIGHT:
			request += "R";
			break;
		default:
			break;
		}
		request += " " + std::to_string(PERSONAL_ID_PUBLIC) + " ";
		request += std::to_string(PERSONAL_ID_PRIVATE);
	}

};
