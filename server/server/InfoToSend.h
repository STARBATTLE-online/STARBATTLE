#pragma once
#include "MapCreator.h"
#include "boost_asio.h"

class InfoToSend
{
public:
	InfoToSend();
	~InfoToSend();

	//��� ���� ��������. ��������, ��� � �� ������� ���� ����������, ���� ��� �� ������� �������.
	//�� � ���������� ��, ��� ����, ����������.
	
private:
	std::string to_send;

};
